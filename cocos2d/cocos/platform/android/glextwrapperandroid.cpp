#define glClearDepth        glClearDepthf
#define glDeleteVertexArrays    glDeleteVertexArraysOES
#define glGenVertexArrays     glGenVertexArraysOES
#define glBindVertexArray     glBindVertexArrayOES
#define glMapBuffer         glMapBufferOES
#define glUnmapBuffer       glUnmapBufferOES

#define GL_DEPTH24_STENCIL8     GL_DEPTH24_STENCIL8_OES
#define GL_WRITE_ONLY       GL_WRITE_ONLY_OES

// GL_GLEXT_PROTOTYPES isn't defined in glplatform.h on android ndk r7 
// we manually define it here
#include <GLES2/gl2platform.h>
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#undef GL_OES_EGL_image
#undef GL_OES_get_program_binary
#undef GL_OES_mapbuffer
#undef GL_OES_texture_3D
#undef GL_OES_vertex_array_object
#undef GL_AMD_performance_monitor
#undef GL_EXT_discard_framebuffer
#undef GL_EXT_multi_draw_arrays
#undef GL_IMG_multisampled_render_to_texture
#undef GL_NV_fence
#undef GL_NV_coverage_sample
#undef GL_QCOM_driver_control
#undef GL_QCOM_extended_get
#undef GL_QCOM_extended_get2
#undef GL_QCOM_tiled_rendering

#include "glwrapperandroid.h"
#include "glextwrapperandroid.h"
#include "base/CCMacros.h"
#include <pthread.h>
extern pthread_t MAIN_THREAD_ID;
//extern void printBackTraceTologToConsole(const char* data);
//bool gl_error = false;
void doCommonGLCheck() {
#if 0
	if( MAIN_THREAD_ID != pthread_self()){
        cocos2d::log("cocos2d: GL thread error" );
        return;
    }
	 GLenum err = glGetError();
    if( err != GL_NO_ERROR )
    {
        cocos2d::log("cocos2d: GL error:0x%04X",err );
        return;
    }
#endif
}
//void if_glwrapper::glEGLImageTargetTexture2DOES (GLenum target, GLeglImageOES image)
//{
//   ::glEGLImageTargetTexture2DOES(target,image);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glEGLImageTargetRenderbufferStorageOES (GLenum target, GLeglImageOES image)
//{
//   ::glEGLImageTargetRenderbufferStorageOES(target,image);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glGetProgramBinaryOES (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, GLvoid *binary)
//{
//   ::glGetProgramBinaryOES(program,bufSize,length,binaryFormat,binary);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glProgramBinaryOES (GLuint program, GLenum binaryFormat, const GLvoid *binary, GLint length)
//{
//   ::glProgramBinaryOES(program,binaryFormat,binary,length);
//    doCommonGLCheck();
//}
//
//
void* if_glwrapper::glMapBufferOES (GLenum target, GLenum access)
{
   void* ret =
   ::glMapBufferOES(target,access);
    doCommonGLCheck();
    return ret;
}


GLboolean if_glwrapper::glUnmapBufferOES (GLenum target)
{
   GLboolean ret =
   ::glUnmapBufferOES(target);
    doCommonGLCheck();
    return ret;
}
//
//
//void if_glwrapper::glGetBufferPointervOES (GLenum target, GLenum pname, GLvoid** params)
//{
//   ::glGetBufferPointervOES(target,pname,params);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glTexImage3DOES (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
//{
//   ::glTexImage3DOES(target,level,internalformat,width,height,depth,border,format,type,pixels);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glTexSubImage3DOES (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* pixels)
//{
//   ::glTexSubImage3DOES(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glCopyTexSubImage3DOES (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
//{
//   ::glCopyTexSubImage3DOES(target,level,xoffset,yoffset,zoffset,x,y,width,height);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glCompressedTexImage3DOES (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data)
//{
//   ::glCompressedTexImage3DOES(target,level,internalformat,width,height,depth,border,imageSize,data);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glCompressedTexSubImage3DOES (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* data)
//{
//   ::glCompressedTexSubImage3DOES(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glFramebufferTexture3DOES (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
//{
//   ::glFramebufferTexture3DOES(target,attachment,textarget,texture,level,zoffset);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glBindVertexArrayOES (GLuint array)
//{
//   ::glBindVertexArrayOES(array);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glDeleteVertexArraysOES (GLsizei n, const GLuint *arrays)
//{
//   ::glDeleteVertexArraysOES(n,arrays);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glGenVertexArraysOES (GLsizei n, GLuint *arrays)
//{
//   ::glGenVertexArraysOES(n,arrays);
//    doCommonGLCheck();
//}
//
//
//GLboolean if_glwrapper::glIsVertexArrayOES (GLuint array)
//{
//   GLboolean ret =
//   ::glIsVertexArrayOES(array);
//    doCommonGLCheck();
//    return ret;
//}
//
//
//void if_glwrapper::glGetPerfMonitorGroupsAMD (GLint *numGroups, GLsizei groupsSize, GLuint *groups)
//{
//   ::glGetPerfMonitorGroupsAMD(numGroups,groupsSize,groups);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glGetPerfMonitorCountersAMD (GLuint group, GLint *numCounters, GLint *maxActiveCounters, GLsizei counterSize, GLuint *counters)
//{
//   ::glGetPerfMonitorCountersAMD(group,numCounters,maxActiveCounters,counterSize,counters);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glGetPerfMonitorGroupStringAMD (GLuint group, GLsizei bufSize, GLsizei *length, GLchar *groupString)
//{
//   ::glGetPerfMonitorGroupStringAMD(group,bufSize,length,groupString);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glGetPerfMonitorCounterStringAMD (GLuint group, GLuint counter, GLsizei bufSize, GLsizei *length, GLchar *counterString)
//{
//   ::glGetPerfMonitorCounterStringAMD(group,counter,bufSize,length,counterString);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glGetPerfMonitorCounterInfoAMD (GLuint group, GLuint counter, GLenum pname, GLvoid *data)
//{
//   ::glGetPerfMonitorCounterInfoAMD(group,counter,pname,data);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glGenPerfMonitorsAMD (GLsizei n, GLuint *monitors)
//{
//   ::glGenPerfMonitorsAMD(n,monitors);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glDeletePerfMonitorsAMD (GLsizei n, GLuint *monitors)
//{
//   ::glDeletePerfMonitorsAMD(n,monitors);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glSelectPerfMonitorCountersAMD (GLuint monitor, GLboolean enable, GLuint group, GLint numCounters, GLuint *countersList)
//{
//   ::glSelectPerfMonitorCountersAMD(monitor,enable,group,numCounters,countersList);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glBeginPerfMonitorAMD (GLuint monitor)
//{
//   ::glBeginPerfMonitorAMD(monitor);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glEndPerfMonitorAMD (GLuint monitor)
//{
//   ::glEndPerfMonitorAMD(monitor);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glGetPerfMonitorCounterDataAMD (GLuint monitor, GLenum pname, GLsizei dataSize, GLuint *data, GLint *bytesWritten)
//{
//   ::glGetPerfMonitorCounterDataAMD(monitor,pname,dataSize,data,bytesWritten);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glDiscardFramebufferEXT (GLenum target, GLsizei numAttachments, const GLenum *attachments)
//{
//   ::glDiscardFramebufferEXT(target,numAttachments,attachments);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glMultiDrawArraysEXT (GLenum mode, GLint *first, GLsizei *count, GLsizei primcount)
//{
//   ::glMultiDrawArraysEXT(mode,first,count,primcount);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glMultiDrawElementsEXT (GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount)
//{
//   ::glMultiDrawElementsEXT(mode,count,type,indices,primcount);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glRenderbufferStorageMultisampleIMG (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
//{
//   ::glRenderbufferStorageMultisampleIMG(target,samples,internalformat,width,height);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glFramebufferTexture2DMultisampleIMG (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples)
//{
//   ::glFramebufferTexture2DMultisampleIMG(target,attachment,textarget,texture,level,samples);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glDeleteFencesNV (GLsizei n, const GLuint *fences)
//{
//   ::glDeleteFencesNV(n,fences);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glGenFencesNV (GLsizei n, GLuint *fences)
//{
//   ::glGenFencesNV(n,fences);
//    doCommonGLCheck();
//}
//
//
//GLboolean if_glwrapper::glIsFenceNV (GLuint fence)
//{
//   GLboolean ret =
//   ::glIsFenceNV(fence);
//    doCommonGLCheck();
//    return ret;
//}
//
//
//GLboolean if_glwrapper::glTestFenceNV (GLuint fence)
//{
//   GLboolean ret =
//   ::glTestFenceNV(fence);
//    doCommonGLCheck();
//    return ret;
//}
//
//
//void if_glwrapper::glGetFenceivNV (GLuint fence, GLenum pname, GLint *params)
//{
//   ::glGetFenceivNV(fence,pname,params);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glFinishFenceNV (GLuint fence)
//{
//   ::glFinishFenceNV(fence);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glSetFenceNV (GLuint fence, GLenum condition)
//{
//   ::glSetFenceNV(fence,condition);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glCoverageMaskNV (GLboolean mask)
//{
//   ::glCoverageMaskNV(mask);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glCoverageOperationNV (GLenum operation)
//{
//   ::glCoverageOperationNV(operation);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glGetDriverControlsQCOM (GLint *num, GLsizei size, GLuint *driverControls)
//{
//   ::glGetDriverControlsQCOM(num,size,driverControls);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glGetDriverControlStringQCOM (GLuint driverControl, GLsizei bufSize, GLsizei *length, GLchar *driverControlString)
//{
//   ::glGetDriverControlStringQCOM(driverControl,bufSize,length,driverControlString);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glEnableDriverControlQCOM (GLuint driverControl)
//{
//   ::glEnableDriverControlQCOM(driverControl);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glDisableDriverControlQCOM (GLuint driverControl)
//{
//   ::glDisableDriverControlQCOM(driverControl);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *numTextures)
//{
//   ::glExtGetTexturesQCOM(textures,maxTextures,numTextures);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *numBuffers)
//{
//   ::glExtGetBuffersQCOM(buffers,maxBuffers,numBuffers);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *numRenderbuffers)
//{
//   ::glExtGetRenderbuffersQCOM(renderbuffers,maxRenderbuffers,numRenderbuffers);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *numFramebuffers)
//{
//   ::glExtGetFramebuffersQCOM(framebuffers,maxFramebuffers,numFramebuffers);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params)
//{
//   ::glExtGetTexLevelParameterivQCOM(texture,face,level,pname,params);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glExtTexObjectStateOverrideiQCOM (GLenum target, GLenum pname, GLint param)
//{
//   ::glExtTexObjectStateOverrideiQCOM(target,pname,param);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glExtGetTexSubImageQCOM (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid *texels)
//{
//   ::glExtGetTexSubImageQCOM(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,texels);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glExtGetBufferPointervQCOM (GLenum target, GLvoid **params)
//{
//   ::glExtGetBufferPointervQCOM(target,params);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *numShaders)
//{
//   ::glExtGetShadersQCOM(shaders,maxShaders,numShaders);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *numPrograms)
//{
//   ::glExtGetProgramsQCOM(programs,maxPrograms,numPrograms);
//    doCommonGLCheck();
//}
//
//
//GLboolean if_glwrapper::glExtIsProgramBinaryQCOM (GLuint program)
//{
//   GLboolean ret =
//   ::glExtIsProgramBinaryQCOM(program);
//    doCommonGLCheck();
//    return ret;
//}
//
//
//void if_glwrapper::glExtGetProgramBinarySourceQCOM (GLuint program, GLenum shadertype, GLchar *source, GLint *length)
//{
//   ::glExtGetProgramBinarySourceQCOM(program,shadertype,source,length);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glStartTilingQCOM (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask)
//{
//   ::glStartTilingQCOM(x,y,width,height,preserveMask);
//    doCommonGLCheck();
//}
//
//
//void if_glwrapper::glEndTilingQCOM (GLbitfield preserveMask)
//{
//   ::glEndTilingQCOM(preserveMask);
//    doCommonGLCheck();
//}


