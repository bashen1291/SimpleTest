#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "glwrapper.h"
#include "glextwrapper.h"
#include "CCConsole.h"
#include <pthread.h>
extern pthread_t MAIN_THREAD_ID;
//extern void printBackTraceTologToConsole(const char* data);
bool gl_error =false;
void doCommonGLCheck() {
#if 0
    if( MAIN_THREAD_ID != pthread_self()){
        cocos2d::log("cocos2d: GL thread error:0x%04X",err );
    }
    
    GLenum err = glGetError();
    if( err != GL_NO_ERROR )
    {
        cocos2d::log("cocos2d: GL error:0x%04X",err );
        return;
    }
#endif
}
GLvoid if_glwrapper::glCopyTextureLevelsAPPLE(GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount)
{
    ::glCopyTextureLevelsAPPLE(destinationTexture,sourceTexture,sourceBaseLevel,sourceLevelCount);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glRenderbufferStorageMultisampleAPPLE(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
    ::glRenderbufferStorageMultisampleAPPLE(target,samples,internalformat,width,height);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glResolveMultisampleFramebufferAPPLE()
{
    ::glResolveMultisampleFramebufferAPPLE();
    doCommonGLCheck();
}


GLsync if_glwrapper::glFenceSyncAPPLE(GLenum condition, GLbitfield flags)
{
    GLsync ret =
    ::glFenceSyncAPPLE(condition,flags);
    doCommonGLCheck();
    return ret;
}


GLboolean if_glwrapper::glIsSyncAPPLE(GLsync sync)
{
    GLboolean ret =
    ::glIsSyncAPPLE(sync);
    doCommonGLCheck();
    return ret;
}


void if_glwrapper::glDeleteSyncAPPLE(GLsync sync)
{
    ::glDeleteSyncAPPLE(sync);
    doCommonGLCheck();
}


GLenum if_glwrapper::glClientWaitSyncAPPLE(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
    GLenum ret =
    ::glClientWaitSyncAPPLE(sync,flags,timeout);
    doCommonGLCheck();
    return ret;
}


void if_glwrapper::glWaitSyncAPPLE(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
    ::glWaitSyncAPPLE(sync,flags,timeout);
    doCommonGLCheck();
}


void if_glwrapper::glGetInteger64vAPPLE(GLenum pname, GLint64 *params)
{
    ::glGetInteger64vAPPLE(pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetSyncivAPPLE(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values)
{
    ::glGetSyncivAPPLE(sync,pname,bufSize,length,values);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glLabelObjectEXT(GLenum type, GLuint object, GLsizei length, const GLchar *label)
{
    ::glLabelObjectEXT(type,object,length,label);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glGetObjectLabelEXT(GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, GLchar *label)
{
    ::glGetObjectLabelEXT(type,object,bufSize,length,label);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glInsertEventMarkerEXT(GLsizei length, const GLchar *marker)
{
    ::glInsertEventMarkerEXT(length,marker);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glPushGroupMarkerEXT(GLsizei length, const GLchar *marker)
{
    ::glPushGroupMarkerEXT(length,marker);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glPopGroupMarkerEXT()
{
    ::glPopGroupMarkerEXT();
    doCommonGLCheck();
}


GLvoid if_glwrapper::glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments)
{
    ::glDiscardFramebufferEXT(target,numAttachments,attachments);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glDrawArraysInstancedEXT(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)
{
    ::glDrawArraysInstancedEXT(mode,first,count,instanceCount);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glDrawElementsInstancedEXT(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei instanceCount)
{
    ::glDrawElementsInstancedEXT(mode,count,type,indices,instanceCount);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glVertexAttribDivisorEXT(GLuint index, GLuint divisor)
{
    ::glVertexAttribDivisorEXT(index,divisor);
    doCommonGLCheck();
}


GLvoid * if_glwrapper::glMapBufferRangeEXT(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
    GLvoid * ret =
    ::glMapBufferRangeEXT(target,offset,length,access);
    doCommonGLCheck();
    return ret;
}


GLvoid if_glwrapper::glFlushMappedBufferRangeEXT(GLenum target, GLintptr offset, GLsizeiptr length)
{
    ::glFlushMappedBufferRangeEXT(target,offset,length);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glGenQueriesEXT(GLsizei n, GLuint *ids)
{
    ::glGenQueriesEXT(n,ids);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glDeleteQueriesEXT(GLsizei n, const GLuint *ids)
{
    ::glDeleteQueriesEXT(n,ids);
    doCommonGLCheck();
}


GLboolean if_glwrapper::glIsQueryEXT(GLuint id)
{
    GLboolean ret =
    ::glIsQueryEXT(id);
    doCommonGLCheck();
    return ret;
}


GLvoid if_glwrapper::glBeginQueryEXT(GLenum target, GLuint id)
{
    ::glBeginQueryEXT(target,id);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glEndQueryEXT(GLenum target)
{
    ::glEndQueryEXT(target);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glGetQueryivEXT(GLenum target, GLenum pname, GLint *params)
{
    ::glGetQueryivEXT(target,pname,params);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glGetQueryObjectuivEXT(GLuint id, GLenum pname, GLuint *params)
{
    ::glGetQueryObjectuivEXT(id,pname,params);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glUseProgramStagesEXT(GLuint pipeline, GLbitfield stages, GLuint program)
{
    ::glUseProgramStagesEXT(pipeline,stages,program);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glActiveShaderProgramEXT(GLuint pipeline, GLuint program)
{
    ::glActiveShaderProgramEXT(pipeline,program);
    doCommonGLCheck();
}


GLuint if_glwrapper::glCreateShaderProgramvEXT(GLenum type, GLsizei count, const GLchar* const *strings)
{
    GLuint ret =
    ::glCreateShaderProgramvEXT(type,count,strings);
    doCommonGLCheck();
    return ret;
}


GLvoid if_glwrapper::glBindProgramPipelineEXT(GLuint pipeline)
{
    ::glBindProgramPipelineEXT(pipeline);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glDeleteProgramPipelinesEXT(GLsizei n, const GLuint *pipelines)
{
    ::glDeleteProgramPipelinesEXT(n,pipelines);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glGenProgramPipelinesEXT(GLsizei n, GLuint *pipelines)
{
    ::glGenProgramPipelinesEXT(n,pipelines);
    doCommonGLCheck();
}


GLboolean if_glwrapper::glIsProgramPipelineEXT(GLuint pipeline)
{
    GLboolean ret =
    ::glIsProgramPipelineEXT(pipeline);
    doCommonGLCheck();
    return ret;
}


GLvoid if_glwrapper::glProgramParameteriEXT(GLuint program, GLenum pname, GLint value)
{
    ::glProgramParameteriEXT(program,pname,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glGetProgramPipelineivEXT(GLuint pipeline, GLenum pname, GLint *params)
{
    ::glGetProgramPipelineivEXT(pipeline,pname,params);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glValidateProgramPipelineEXT(GLuint pipeline)
{
    ::glValidateProgramPipelineEXT(pipeline);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glGetProgramPipelineInfoLogEXT(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    ::glGetProgramPipelineInfoLogEXT(pipeline,bufSize,length,infoLog);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform1iEXT(GLuint program, GLint location, GLint x)
{
    ::glProgramUniform1iEXT(program,location,x);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform2iEXT(GLuint program, GLint location, GLint x, GLint y)
{
    ::glProgramUniform2iEXT(program,location,x,y);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform3iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z)
{
    ::glProgramUniform3iEXT(program,location,x,y,z);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform4iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w)
{
    ::glProgramUniform4iEXT(program,location,x,y,z,w);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform1fEXT(GLuint program, GLint location, GLfloat x)
{
    ::glProgramUniform1fEXT(program,location,x);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform2fEXT(GLuint program, GLint location, GLfloat x, GLfloat y)
{
    ::glProgramUniform2fEXT(program,location,x,y);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform3fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z)
{
    ::glProgramUniform3fEXT(program,location,x,y,z);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform4fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    ::glProgramUniform4fEXT(program,location,x,y,z,w);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
    ::glProgramUniform1ivEXT(program,location,count,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
    ::glProgramUniform2ivEXT(program,location,count,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
    ::glProgramUniform3ivEXT(program,location,count,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)
{
    ::glProgramUniform4ivEXT(program,location,count,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
    ::glProgramUniform1fvEXT(program,location,count,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
    ::glProgramUniform2fvEXT(program,location,count,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
    ::glProgramUniform3fvEXT(program,location,count,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
    ::glProgramUniform4fvEXT(program,location,count,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    ::glProgramUniformMatrix2fvEXT(program,location,count,transpose,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    ::glProgramUniformMatrix3fvEXT(program,location,count,transpose,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    ::glProgramUniformMatrix4fvEXT(program,location,count,transpose,value);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glTexStorage2DEXT(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
    ::glTexStorage2DEXT(target,levels,internalformat,width,height);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glGetBufferPointervOES (GLenum target, GLenum pname, GLvoid **params)
{
    ::glGetBufferPointervOES(target,pname,params);
    doCommonGLCheck();
}


GLvoid * if_glwrapper::glMapBufferOES (GLenum target, GLenum access)
{
    GLvoid * ret =
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


GLvoid if_glwrapper::glBindVertexArrayOES(GLuint array)
{
    ::glBindVertexArrayOES(array);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glDeleteVertexArraysOES(GLsizei n, const GLuint *arrays)
{
    ::glDeleteVertexArraysOES(n,arrays);
    doCommonGLCheck();
}


GLvoid if_glwrapper::glGenVertexArraysOES(GLsizei n, GLuint *arrays)
{
    ::glGenVertexArraysOES(n,arrays);
    doCommonGLCheck();
}


GLboolean if_glwrapper::glIsVertexArrayOES(GLuint array)
{
    GLboolean ret =
    ::glIsVertexArrayOES(array);
    doCommonGLCheck();
    return ret;
}

