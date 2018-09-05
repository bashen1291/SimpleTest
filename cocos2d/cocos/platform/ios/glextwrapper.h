#ifndef __gl_wrapper_es20ext_h_
#define __gl_wrapper_es20ext_h_

#include <glwrapper.h>


namespace if_glwrapper {


#define GL_APPLE_clip_distance                                  1
#define GL_APPLE_color_buffer_packed_float                      1
#define GL_APPLE_copy_texture_levels                            1
#define GL_APPLE_framebuffer_multisample                        1
#define GL_APPLE_rgb_422                                        1
#define GL_APPLE_sync                                           1
#define GL_APPLE_texture_format_BGRA8888                        1
#define GL_APPLE_texture_max_level                              1
#define GL_APPLE_texture_packed_float                           1
#define GL_EXT_blend_minmax                                     1
#define GL_EXT_color_buffer_half_float                          1
#define GL_EXT_debug_label                                      1
#define GL_EXT_debug_marker                                     1
#define GL_EXT_discard_framebuffer                              1
#define GL_EXT_draw_instanced                                   1
#define GL_EXT_instanced_arrays                                 1
#define GL_EXT_map_buffer_range                                 1
#define GL_EXT_occlusion_query_boolean                          1
#define GL_EXT_pvrtc_sRGB                                       1
#define GL_EXT_read_format_bgra                                 1
#define GL_EXT_separate_shader_objects                          1
#define GL_EXT_shader_framebuffer_fetch                         1
#define GL_EXT_shader_texture_lod                               1
#define GL_EXT_shadow_samplers                                  1
#define GL_EXT_sRGB                                             1
#define GL_EXT_texture_filter_anisotropic                       1
#define GL_EXT_texture_rg                                       1
#define GL_EXT_texture_storage                                  1
#define GL_IMG_read_format                                      1
#define GL_IMG_texture_compression_pvrtc                        1
#define GL_OES_depth_texture                                    1
#define GL_OES_depth24                                          1
#define GL_OES_element_index_uint                               1
#define GL_OES_fbo_render_mipmap                                1
#define GL_OES_mapbuffer                                        1
#define GL_OES_packed_depth_stencil                             1
#define GL_OES_rgb8_rgba8                                       1
#define GL_OES_standard_derivatives                             1
#define GL_OES_texture_float                                    1
#define GL_OES_texture_half_float                               1
#define GL_OES_texture_half_float_linear                        1
#define GL_OES_vertex_array_object                              1
#define GL_KHR_texture_compression_astc_ldr                     1

/**************************************************************************/

/*------------------------------------------------------------------------*
 * APPLE extension tokens
 *------------------------------------------------------------------------*/
#if GL_APPLE_color_buffer_packed_float
#define GL_R11F_G11F_B10F_APPLE                                 0x8C3A
#define GL_RGB9_E5_APPLE                                        0x8C3D
#endif

#if GL_APPLE_clip_distance
#define GL_CLIP_DISTANCE0_APPLE           0x3000
#define GL_CLIP_DISTANCE1_APPLE           0x3001
#define GL_CLIP_DISTANCE2_APPLE           0x3002
#define GL_CLIP_DISTANCE3_APPLE           0x3003
#define GL_CLIP_DISTANCE4_APPLE           0x3004
#define GL_CLIP_DISTANCE5_APPLE           0x3005
#define GL_CLIP_DISTANCE6_APPLE           0x3006
#define GL_CLIP_DISTANCE7_APPLE           0x3007
#define GL_MAX_CLIP_DISTANCES_APPLE       0x0D32
#endif

#if GL_APPLE_framebuffer_multisample
#define GL_RENDERBUFFER_SAMPLES_APPLE                           0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE             0x8D56
#define GL_MAX_SAMPLES_APPLE                                    0x8D57
#define GL_READ_FRAMEBUFFER_APPLE                               0x8CA8
#define GL_DRAW_FRAMEBUFFER_APPLE                               0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_APPLE                       0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_APPLE                       0x8CAA
#endif

#if GL_APPLE_texture_packed_float
#define GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE                   0x8C3B
#define GL_UNSIGNED_INT_5_9_9_9_REV_APPLE                       0x8C3E
#endif

#if GL_APPLE_rgb_422
#define GL_RGB_422_APPLE                                        0x8A1F
#define GL_UNSIGNED_SHORT_8_8_APPLE                             0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_APPLE                         0x85BB
#endif

#if GL_APPLE_sync
#define GL_MAX_SERVER_WAIT_TIMEOUT_APPLE                        0x9111
#define GL_OBJECT_TYPE_APPLE                                    0x9112
#define GL_SYNC_CONDITION_APPLE                                 0x9113
#define GL_SYNC_STATUS_APPLE                                    0x9114
#define GL_SYNC_FLAGS_APPLE                                     0x9115
#define GL_SYNC_FENCE_APPLE                                     0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE                     0x9117
#define GL_UNSIGNALED_APPLE                                     0x9118
#define GL_SIGNALED_APPLE                                       0x9119
#define GL_ALREADY_SIGNALED_APPLE                               0x911A
#define GL_TIMEOUT_EXPIRED_APPLE                                0x911B
#define GL_CONDITION_SATISFIED_APPLE                            0x911C
#define GL_WAIT_FAILED_APPLE                                    0x911D
#define GL_SYNC_FLUSH_COMMANDS_BIT_APPLE                        0x00000001
#define GL_TIMEOUT_IGNORED_APPLE                                0xFFFFFFFFFFFFFFFFull
#define GL_SYNC_OBJECT_APPLE                                    0x8A53
#endif

#if GL_APPLE_texture_format_BGRA8888
#define GL_BGRA_EXT                                             0x80E1
#endif

#if GL_APPLE_texture_format_BGRA8888 || GL_IMG_read_format
#define GL_BGRA                                                 0x80E1
#endif

#if GL_APPLE_texture_max_level
#define GL_TEXTURE_MAX_LEVEL_APPLE                              0x813D
#endif

/*------------------------------------------------------------------------*
 * EXT extension tokens
 *------------------------------------------------------------------------*/
#if GL_EXT_blend_minmax
#define GL_MIN_EXT                                              0x8007
#define GL_MAX_EXT                                              0x8008
#endif

#if GL_EXT_color_buffer_half_float
#define GL_RGBA16F_EXT                                          0x881A
#define GL_RGB16F_EXT                                           0x881B
#define GL_RG16F_EXT                                            0x822F
#define GL_R16F_EXT                                             0x822D
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT            0x8211
#define GL_UNSIGNED_NORMALIZED_EXT                              0x8C17
#endif

#if GL_EXT_debug_label
#define GL_BUFFER_OBJECT_EXT                                    0x9151
#define GL_SHADER_OBJECT_EXT                                    0x8B48
#define GL_PROGRAM_OBJECT_EXT                                   0x8B40
#define GL_QUERY_OBJECT_EXT                                     0x9153
#define GL_VERTEX_ARRAY_OBJECT_EXT                              0x9154
#define GL_PROGRAM_PIPELINE_OBJECT_EXT                          0x8A4F
/*      GL_SYNC_OBJECT_APPLE */
#endif

#if GL_EXT_discard_framebuffer
#define GL_COLOR_EXT                                            0x1800
#define GL_DEPTH_EXT                                            0x1801
#define GL_STENCIL_EXT                                          0x1802
#endif

#if GL_EXT_instanced_arrays
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_EXT                      0x88FE
#endif

#if GL_EXT_map_buffer_range
#define GL_MAP_READ_BIT_EXT                                     0x0001
#define GL_MAP_WRITE_BIT_EXT                                    0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT_EXT                         0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT_EXT                        0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT_EXT                           0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT_EXT                           0x0020
#endif

#if GL_EXT_occlusion_query_boolean
#define GL_ANY_SAMPLES_PASSED_EXT                               0x8C2F
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT                  0x8D6A
#define GL_CURRENT_QUERY_EXT                                    0x8865
#define GL_QUERY_RESULT_EXT                                     0x8866
#define GL_QUERY_RESULT_AVAILABLE_EXT                           0x8867
#endif

#if GL_EXT_pvrtc_sRGB
#define GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT                     0x8A54
#define GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT                     0x8A55
#define GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT               0x8A56
#define GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT               0x8A57
#endif

#if GL_EXT_read_format_bgra
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT                       0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT                       0x8366
#define GL_UNSIGNED_SHORT_1_5_5_5_REV                           0x8366
#endif

#if GL_EXT_read_format_bgra || GL_IMG_read_format
#define GL_UNSIGNED_SHORT_4_4_4_4_REV                           0x8365
#endif

#if GL_EXT_separate_shader_objects
#define GL_VERTEX_SHADER_BIT_EXT                                0x00000001
#define GL_FRAGMENT_SHADER_BIT_EXT                              0x00000002
#define GL_ALL_SHADER_BITS_EXT                                  0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE_EXT                                0x8258
#define GL_ACTIVE_PROGRAM_EXT                                   0x8259
#define GL_PROGRAM_PIPELINE_BINDING_EXT                         0x825A
#endif

#if GL_EXT_shader_framebuffer_fetch
#define GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT                 0x8A52
#endif

#if GL_EXT_shadow_samplers
#define GL_TEXTURE_COMPARE_MODE_EXT                             0x884C
#define GL_TEXTURE_COMPARE_FUNC_EXT                             0x884D
#define GL_COMPARE_REF_TO_TEXTURE_EXT                           0x884E
#define GL_SAMPLER_2D_SHADOW_EXT                                0x8B62
#endif

#if GL_EXT_sRGB
#define GL_SRGB_EXT                                             0x8C40
#define GL_SRGB_ALPHA_EXT                                       0x8C42
#define GL_SRGB8_ALPHA8_EXT                                     0x8C43
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT            0x8210
#endif

#if GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT                           0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT                       0x84FF
#endif

#if GL_EXT_texture_rg
#define GL_RED_EXT                                              0x1903
#define GL_RG_EXT                                               0x8227
#define GL_R8_EXT                                               0x8229
#define GL_RG8_EXT                                              0x822B
#endif

#if GL_EXT_texture_storage
#define GL_TEXTURE_IMMUTABLE_FORMAT_EXT                         0x912F
#define GL_ALPHA8_EXT                                           0x803C
#define GL_LUMINANCE8_EXT                                       0x8040
#define GL_LUMINANCE8_ALPHA8_EXT                                0x8045
#define GL_BGRA8_EXT                                            0x93A1
#define GL_RGBA32F_EXT                                          0x8814
#define GL_RGB32F_EXT                                           0x8815
#define GL_RG32F_EXT                                            0x8230
#define GL_R32F_EXT                                             0x822E
#define GL_ALPHA32F_EXT                                         0x8816
#define GL_LUMINANCE32F_EXT                                     0x8818
#define GL_LUMINANCE_ALPHA32F_EXT                               0x8819
#define GL_ALPHA16F_EXT                                         0x881C
#define GL_LUMINANCE16F_EXT                                     0x881E
#define GL_LUMINANCE_ALPHA16F_EXT                               0x881F
#define GL_DEPTH_COMPONENT32_OES                                0x81A7
#define GL_RGB_RAW_422_APPLE                                    0x8A51
#endif

/*------------------------------------------------------------------------*
 * IMG extension tokens
 *------------------------------------------------------------------------*/
#if GL_IMG_read_format
#define GL_BGRA_IMG                                             0x80E1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG                       0x8365
#endif

#if GL_IMG_texture_compression_pvrtc
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG                      0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG                      0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG                     0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG                     0x8C03
#endif

/*------------------------------------------------------------------------*
 * OES extension tokens
 *------------------------------------------------------------------------*/
#if GL_OES_depth24
#define GL_DEPTH_COMPONENT24_OES                                0x81A6
#endif

#if GL_OES_mapbuffer
#define GL_WRITE_ONLY_OES                                       0x88B9
#define GL_BUFFER_ACCESS_OES                                    0x88BB
#define GL_BUFFER_MAPPED_OES                                    0x88BC
#define GL_BUFFER_MAP_POINTER_OES                               0x88BD
#endif

#if GL_OES_packed_depth_stencil
#define GL_DEPTH_STENCIL_OES                                    0x84F9
#define GL_UNSIGNED_INT_24_8_OES                                0x84FA
#define GL_DEPTH24_STENCIL8_OES                                 0x88F0
#endif

#if GL_OES_rgb8_rgba8
#define GL_RGB8_OES                                             0x8051
#define GL_RGBA8_OES                                            0x8058
#endif

#if GL_OES_standard_derivatives
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES                  0x8B8B
#endif

#if GL_OES_texture_half_float
#define GL_HALF_FLOAT_OES                                       0x8D61
#endif

#if GL_OES_vertex_array_object
#define GL_VERTEX_ARRAY_BINDING_OES                             0x85B5
#endif


#if GL_KHR_texture_compression_astc_ldr
#define GL_COMPRESSED_RGBA_ASTC_4x4_KHR                         0x93B0
#define GL_COMPRESSED_RGBA_ASTC_5x4_KHR                         0x93B1
#define GL_COMPRESSED_RGBA_ASTC_5x5_KHR                         0x93B2
#define GL_COMPRESSED_RGBA_ASTC_6x5_KHR                         0x93B3
#define GL_COMPRESSED_RGBA_ASTC_6x6_KHR                         0x93B4
#define GL_COMPRESSED_RGBA_ASTC_8x5_KHR                         0x93B5
#define GL_COMPRESSED_RGBA_ASTC_8x6_KHR                         0x93B6
#define GL_COMPRESSED_RGBA_ASTC_8x8_KHR                         0x93B7
#define GL_COMPRESSED_RGBA_ASTC_10x5_KHR                        0x93B8
#define GL_COMPRESSED_RGBA_ASTC_10x6_KHR                        0x93B9
#define GL_COMPRESSED_RGBA_ASTC_10x8_KHR                        0x93BA
#define GL_COMPRESSED_RGBA_ASTC_10x10_KHR                       0x93BB
#define GL_COMPRESSED_RGBA_ASTC_12x10_KHR                       0x93BC
#define GL_COMPRESSED_RGBA_ASTC_12x12_KHR                       0x93BD
#endif

/**************************************************************************/

/*------------------------------------------------------------------------*
 * APPLE extension functions
 *------------------------------------------------------------------------*/
#if GL_APPLE_copy_texture_levels
 GLvoid glCopyTextureLevelsAPPLE(GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount) ;
#endif

#if GL_APPLE_framebuffer_multisample
 GLvoid glRenderbufferStorageMultisampleAPPLE(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)  ;
 GLvoid glResolveMultisampleFramebufferAPPLE(void)  ;
#endif

#if GL_APPLE_sync
 GLsync glFenceSyncAPPLE(GLenum condition, GLbitfield flags) ;
 GLboolean glIsSyncAPPLE(GLsync sync) ;
 void glDeleteSyncAPPLE(GLsync sync) ;
 GLenum glClientWaitSyncAPPLE(GLsync sync, GLbitfield flags, GLuint64 timeout) ;
 void glWaitSyncAPPLE(GLsync sync, GLbitfield flags, GLuint64 timeout) ;
 void glGetInteger64vAPPLE(GLenum pname, GLint64 *params) ;
 void glGetSyncivAPPLE(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values) ;
#endif

/*------------------------------------------------------------------------*
 * EXT extension functions
 *------------------------------------------------------------------------*/
#if GL_EXT_debug_label
 GLvoid glLabelObjectEXT(GLenum type, GLuint object, GLsizei length, const GLchar *label)  ;
 GLvoid glGetObjectLabelEXT(GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, GLchar *label)  ;
#endif

#if GL_EXT_debug_marker
 GLvoid glInsertEventMarkerEXT(GLsizei length, const GLchar *marker)  ;
 GLvoid glPushGroupMarkerEXT(GLsizei length, const GLchar *marker)  ;
 GLvoid glPopGroupMarkerEXT(void)  ;
#endif

#if GL_EXT_discard_framebuffer
 GLvoid  glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments)  ;
#endif

#if GL_EXT_draw_instanced
 GLvoid glDrawArraysInstancedEXT(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)  ;
 GLvoid glDrawElementsInstancedEXT(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei instanceCount)  ;
#endif

#if GL_EXT_instanced_arrays
 GLvoid glVertexAttribDivisorEXT(GLuint index, GLuint divisor)  ;
#endif

#if GL_EXT_map_buffer_range
 GLvoid *glMapBufferRangeEXT(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) ;
 GLvoid glFlushMappedBufferRangeEXT(GLenum target, GLintptr offset, GLsizeiptr length) ;
#endif

#if GL_EXT_occlusion_query_boolean
 GLvoid glGenQueriesEXT(GLsizei n, GLuint *ids)  ;
 GLvoid glDeleteQueriesEXT(GLsizei n, const GLuint *ids)  ;
 GLboolean glIsQueryEXT(GLuint id)  ;
 GLvoid glBeginQueryEXT(GLenum target, GLuint id)  ;
 GLvoid glEndQueryEXT(GLenum target)  ;
 GLvoid glGetQueryivEXT(GLenum target, GLenum pname, GLint *params)  ;
 GLvoid glGetQueryObjectuivEXT(GLuint id, GLenum pname, GLuint *params)  ;
#endif

#if GL_EXT_separate_shader_objects
 GLvoid glUseProgramStagesEXT(GLuint pipeline, GLbitfield stages, GLuint program)  ;
 GLvoid glActiveShaderProgramEXT(GLuint pipeline, GLuint program)  ;
 GLuint glCreateShaderProgramvEXT(GLenum type, GLsizei count, const GLchar* const *strings)  ;
 GLvoid glBindProgramPipelineEXT(GLuint pipeline)  ;
 GLvoid glDeleteProgramPipelinesEXT(GLsizei n, const GLuint *pipelines)  ;
 GLvoid glGenProgramPipelinesEXT(GLsizei n, GLuint *pipelines)  ;
 GLboolean glIsProgramPipelineEXT(GLuint pipeline)  ;
 GLvoid glProgramParameteriEXT(GLuint program, GLenum pname, GLint value)  ;
 GLvoid glGetProgramPipelineivEXT(GLuint pipeline, GLenum pname, GLint *params)  ;
 GLvoid glValidateProgramPipelineEXT(GLuint pipeline)  ;
 GLvoid glGetProgramPipelineInfoLogEXT(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog)  ;

 GLvoid glProgramUniform1iEXT(GLuint program, GLint location, GLint x)  ;
 GLvoid glProgramUniform2iEXT(GLuint program, GLint location, GLint x, GLint y)  ;
 GLvoid glProgramUniform3iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z)  ;
 GLvoid glProgramUniform4iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w)  ;

 GLvoid glProgramUniform1fEXT(GLuint program, GLint location, GLfloat x)  ;
 GLvoid glProgramUniform2fEXT(GLuint program, GLint location, GLfloat x, GLfloat y)  ;
 GLvoid glProgramUniform3fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z)  ;
 GLvoid glProgramUniform4fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)  ;

 GLvoid glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)  ;
 GLvoid glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)  ;
 GLvoid glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)  ;
 GLvoid glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)  ;

 GLvoid glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)  ;
 GLvoid glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)  ;
 GLvoid glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)  ;
 GLvoid glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)  ;

 GLvoid glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)  ;
 GLvoid glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)  ;
 GLvoid glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)  ;
#endif

#if GL_EXT_texture_storage
 GLvoid glTexStorage2DEXT(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) ;
#endif

/*------------------------------------------------------------------------*
 * OES extension functions
 *------------------------------------------------------------------------*/
#if GL_OES_mapbuffer
 GLvoid  glGetBufferPointervOES (GLenum target, GLenum pname, GLvoid **params);
 GLvoid *  glMapBufferOES (GLenum target, GLenum access);
 GLboolean  glUnmapBufferOES (GLenum target);
#endif

#if GL_OES_vertex_array_object
 GLvoid glBindVertexArrayOES(GLuint array)  ;
 GLvoid glDeleteVertexArraysOES(GLsizei n, const GLuint *arrays)  ;
 GLvoid glGenVertexArraysOES(GLsizei n, GLuint *arrays)  ;
 GLboolean glIsVertexArrayOES(GLuint array)  ;
#endif

}


#endif /* __gl_wrapper_es20ext_h_ */
