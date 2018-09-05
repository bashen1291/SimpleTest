//
//  IFAppController.h
//  IF
//
//  Created by 吴 凌江 on 13-8-28.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#ifdef METAL_ENABLE
#import "RootViewControllerMetal.h"
#import "string"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCSafeNotificationCenter.h"
#include "SimpleCommand.h"
#import "SharedStructures.h"

//@import simd;
//@import ModelIO;

extern std::string g_theBranchLinkData;
static RootViewControllerMetal* theRootViewControllerMetal = nil;

// The max number of command buffers in flight
static const NSUInteger kMaxInflightBuffers = 3;

// Max API memory buffer size.
static const size_t kMaxBytesPerFrame = 1024*1024;

@interface RootViewControllerMetal () {
    MTKView* m_metalView;
    UIView*  m_glView;

    // controller
    dispatch_semaphore_t _inflight_semaphore;
    id <MTLBuffer> _dynamicConstantBuffer;
    uint8_t _constantDataBufferIndex;

    // renderer
    id <MTLDevice> _device;
    id <MTLCommandQueue> _commandQueue;
    id <MTLLibrary> _defaultLibrary;
    id <MTLRenderPipelineState> _pipelineState;
    id <MTLDepthStencilState> _depthState;

    // uniforms
    matrix_float4x4 _projectionMatrix;
    matrix_float4x4 _viewMatrix;
    uniforms_t _uniform_buffer;
    float _rotation;

    // meshes
    MTKMesh *_boxMesh;
}
@end

@implementation RootViewControllerMetal

@synthesize completionDelegate;

+(RootViewControllerMetal*)shared {
    return theRootViewControllerMetal;
}

+ (void)afterGetBranchData:(NSDictionary *)data {
    //  {"+is_first_session":0,"+clicked_branch_link":0}
    if(data == nil || [data count] == 2) {
        return;
    }
    g_theBranchLinkData.clear();
    NSMutableString* strJson = [[NSMutableString alloc] init];
    [strJson appendString:@"{"];
    NSArray* keyList = [data allKeys];
    for(int i = [keyList count]; i > 0; i--) {
        id key = [keyList objectAtIndex:(i - 1)];
        id value = [data objectForKey: key];
        NSLog (@"Key: %@ for value: %@", key, value);
        if ( [value isKindOfClass:[NSNumber class]] ) {
            if(i > 1) {
                [strJson appendFormat:@"\"%@\":%d,", key, [value integerValue]];
            } else {
                [strJson appendFormat:@"\"%@\":%d", key, [value integerValue]];
            }
        } else {
            if(i > 1) {
                [strJson appendFormat:@"\"%@\":\"%@\",", key, value];
            } else {
                [strJson appendFormat:@"\"%@\":\"%@\"", key, value];
            }
        }
    }
    [strJson appendString:@"}"];
    NSLOG(@"theBranchLinkData: %@", strJson);
    if([strJson length] <= 250) {
        g_theBranchLinkData.append([strJson UTF8String], [strJson length]);
        cocos2d::extension::CCSafeNotificationCenter::sharedNotificationCenter()->postNotification("BranchLinkData");
        CCUserDefault::sharedUserDefault()->setStringForKey("BranchLinkData", g_theBranchLinkData.c_str());
        CCUserDefault::sharedUserDefault()->flush();
    }
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
        theRootViewControllerMetal = self;
    }
    return self;
}

- (void)configureControlWithData:(NSDictionary *)data {
    [RootViewControllerMetal afterGetBranchData:data];
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [[Branch getInstance] registerDeepLinkController:self forKey:@"ljlastwars"];

    _constantDataBufferIndex = 0;
    _inflight_semaphore = dispatch_semaphore_create(3);

    [self _setupMetal];
    [self _setupView];
    [self _loadAssets];
    [self _reshape];
}

// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskPortrait;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
    [self.completionDelegate deepLinkingControllerCompleted];
}

-(void)setMetalView:(MTKView*)metalView
             glView:(UIView*)glView {
    m_metalView = metalView;
    m_glView = glView;
}

- (void)_setupView
{
    m_metalView.device = _device;
    m_metalView.delegate = self;

    // Setup the render target, choose values based on your app
    m_metalView.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
}

- (void)_setupMetal
{
    // Set the view to use the default device
    _device = MTLCreateSystemDefaultDevice();

    // Create a new command queue
    _commandQueue = [_device newCommandQueue];

    // Load all the shader files with a metal file extension in the project
    _defaultLibrary = [_device newDefaultLibrary];
}

- (void)_loadAssets
{
    // Generate meshes
    MDLMesh *mdl = [MDLMesh newBoxWithDimensions:(vector_float3){2,2,2} segments:(vector_uint3){1,1,1}
                                    geometryType:MDLGeometryTypeTriangles inwardNormals:NO
                                       allocator:[[MTKMeshBufferAllocator alloc] initWithDevice: _device]];

    _boxMesh = [[MTKMesh alloc] initWithMesh:mdl device:_device error:nil];

    // Allocate one region of memory for the uniform buffer
    _dynamicConstantBuffer = [_device newBufferWithLength:kMaxBytesPerFrame options:0];
    _dynamicConstantBuffer.label = @"UniformBuffer";

    // Load the fragment program into the library
    id <MTLFunction> fragmentProgram = [_defaultLibrary newFunctionWithName:@"lighting_fragment"];

    // Load the vertex program into the library
    id <MTLFunction> vertexProgram = [_defaultLibrary newFunctionWithName:@"lighting_vertex"];

    // Create a vertex descriptor from the MTKMesh
    MTLVertexDescriptor *vertexDescriptor = MTKMetalVertexDescriptorFromModelIO(_boxMesh.vertexDescriptor);
    vertexDescriptor.layouts[0].stepRate = 1;
    vertexDescriptor.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;

    // Create a reusable pipeline state
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.label = @"MyPipeline";
    pipelineStateDescriptor.sampleCount = m_metalView.sampleCount;
    pipelineStateDescriptor.vertexFunction = vertexProgram;
    pipelineStateDescriptor.fragmentFunction = fragmentProgram;
    pipelineStateDescriptor.vertexDescriptor = vertexDescriptor;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = m_metalView.colorPixelFormat;
    pipelineStateDescriptor.depthAttachmentPixelFormat = m_metalView.depthStencilPixelFormat;
    pipelineStateDescriptor.stencilAttachmentPixelFormat = m_metalView.depthStencilPixelFormat;

    NSError *error = NULL;
    _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error];
    if (!_pipelineState) {
        NSLOG(@"Failed to created pipeline state, error %@", error);
    }

    MTLDepthStencilDescriptor *depthStateDesc = [[MTLDepthStencilDescriptor alloc] init];
    depthStateDesc.depthCompareFunction = MTLCompareFunctionLess;
    depthStateDesc.depthWriteEnabled = YES;
    _depthState = [_device newDepthStencilStateWithDescriptor:depthStateDesc];
}

- (void)_render
{
    dispatch_semaphore_wait(_inflight_semaphore, DISPATCH_TIME_FOREVER);

    [self _update];

    // Create a new command buffer for each renderpass to the current drawable
    id <MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
    commandBuffer.label = @"MyCommand";

    // Call the view's completion handler which is required by the view since it will signal its semaphore and set up the next buffer
    __block dispatch_semaphore_t block_sema = _inflight_semaphore;
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
        dispatch_semaphore_signal(block_sema);
    }];

    // Obtain a renderPassDescriptor generated from the view's drawable textures
    MTLRenderPassDescriptor* renderPassDescriptor = m_metalView.currentRenderPassDescriptor;

    if(renderPassDescriptor != nil) // If we have a valid drawable, begin the commands to render into it
    {
        // Create a render command encoder so we can render into something
        id <MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        renderEncoder.label = @"MyRenderEncoder";
        [renderEncoder setDepthStencilState:_depthState];

        // Set context state
        [renderEncoder pushDebugGroup:@"DrawCube"];
        [renderEncoder setRenderPipelineState:_pipelineState];
        [renderEncoder setVertexBuffer:_boxMesh.vertexBuffers[0].buffer offset:_boxMesh.vertexBuffers[0].offset atIndex:0 ];
        [renderEncoder setVertexBuffer:_dynamicConstantBuffer offset:(sizeof(uniforms_t) * _constantDataBufferIndex) atIndex:1 ];

        MTKSubmesh* submesh = _boxMesh.submeshes[0];
        // Tell the render context we want to draw our primitives
        [renderEncoder drawIndexedPrimitives:submesh.primitiveType indexCount:submesh.indexCount indexType:submesh.indexType indexBuffer:submesh.indexBuffer.buffer indexBufferOffset:submesh.indexBuffer.offset];

        [renderEncoder popDebugGroup];

        // We're done encoding commands
        [renderEncoder endEncoding];

        // Schedule a present once the framebuffer is complete using the current drawable
        [commandBuffer presentDrawable:m_metalView.currentDrawable];
    }

    // The render assumes it can now increment the buffer index and that the previous index won't be touched until we cycle back around to the same index
    _constantDataBufferIndex = (_constantDataBufferIndex + 1) % kMaxInflightBuffers;

    // Finalize rendering here & push the command buffer to the GPU
    [commandBuffer commit];
}

- (void)_reshape
{
    // When reshape is called, update the view and projection matricies since this means the view orientation or size changed
    float aspect = fabs(self.view.bounds.size.width / self.view.bounds.size.height);
    _projectionMatrix = matrix_from_perspective_fov_aspectLH(65.0f * (M_PI / 180.0f), aspect, 0.1f, 100.0f);

    _viewMatrix = matrix_identity_float4x4;
}

- (void)_update
{
    matrix_float4x4 base_model = matrix_multiply(matrix_from_translation(0.0f, 0.0f, 5.0f), matrix_from_rotation(_rotation, 0.0f, 1.0f, 0.0f));
    matrix_float4x4 base_mv = matrix_multiply(_viewMatrix, base_model);
    matrix_float4x4 modelViewMatrix = matrix_multiply(base_mv, matrix_from_rotation(_rotation, 1.0f, 1.0f, 1.0f));

    // Load constant buffer data into appropriate buffer at current index
    uniforms_t *uniforms = &((uniforms_t *)[_dynamicConstantBuffer contents])[_constantDataBufferIndex];

    uniforms->normal_matrix = matrix_invert(matrix_transpose(modelViewMatrix));
    uniforms->modelview_projection_matrix = matrix_multiply(_projectionMatrix, modelViewMatrix);
    _rotation += 0.01f;
}

// Called whenever view changes orientation or layout is changed
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    [self _reshape];
}


// Called whenever the view needs to render
- (void)drawInMTKView:(nonnull MTKView *)view
{
    @autoreleasepool {
        [self _render];
    }
}

#pragma mark Utilities

static matrix_float4x4 matrix_from_perspective_fov_aspectLH(const float fovY, const float aspect, const float nearZ, const float farZ)
{
    float yscale = 1.0f / tanf(fovY * 0.5f); // 1 / tan == cot
    float xscale = yscale / aspect;
    float q = farZ / (farZ - nearZ);

    matrix_float4x4 m = {
        .columns[0] = { xscale, 0.0f, 0.0f, 0.0f },
        .columns[1] = { 0.0f, yscale, 0.0f, 0.0f },
        .columns[2] = { 0.0f, 0.0f, q, 1.0f },
        .columns[3] = { 0.0f, 0.0f, q * -nearZ, 0.0f }
    };

    return m;
}

static matrix_float4x4 matrix_from_translation(float x, float y, float z)
{
    matrix_float4x4 m = matrix_identity_float4x4;
    m.columns[3] = (vector_float4) { x, y, z, 1.0 };
    return m;
}

static matrix_float4x4 matrix_from_rotation(float radians, float x, float y, float z)
{
    vector_float3 v = vector_normalize(((vector_float3){x, y, z}));
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);

    matrix_float4x4 m = {
        .columns[0] = {
            cos + cosp * v.x * v.x,
            cosp * v.x * v.y + v.z * sin,
            cosp * v.x * v.z - v.y * sin,
            0.0f,
        },

        .columns[1] = {
            cosp * v.x * v.y - v.z * sin,
            cos + cosp * v.y * v.y,
            cosp * v.y * v.z + v.x * sin,
            0.0f,
        },

        .columns[2] = {
            cosp * v.x * v.z + v.y * sin,
            cosp * v.y * v.z - v.x * sin,
            cos + cosp * v.z * v.z,
            0.0f,
        },

        .columns[3] = { 0.0f, 0.0f, 0.0f, 1.0f
        }
    };
    return m;
}

@end
#endif
