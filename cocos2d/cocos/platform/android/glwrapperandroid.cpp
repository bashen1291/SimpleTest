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
#include "glwrapperandroid.h"
#include "glextwrapperandroid.h"

extern void doCommonGLCheck();

void if_glwrapper::glActiveTexture (GLenum texture)
{
   ::glActiveTexture(texture);
    doCommonGLCheck();
}


void if_glwrapper::glAttachShader (GLuint program, GLuint shader)
{
   ::glAttachShader(program,shader);
    doCommonGLCheck();
}


void if_glwrapper::glBindAttribLocation (GLuint program, GLuint index, const GLchar* name)
{
   ::glBindAttribLocation(program,index,name);
    doCommonGLCheck();
}


void if_glwrapper::glBindBuffer (GLenum target, GLuint buffer)
{
   ::glBindBuffer(target,buffer);
    doCommonGLCheck();
}


void if_glwrapper::glBindFramebuffer (GLenum target, GLuint framebuffer)
{
   ::glBindFramebuffer(target,framebuffer);
    doCommonGLCheck();
}


void if_glwrapper::glBindRenderbuffer (GLenum target, GLuint renderbuffer)
{
   ::glBindRenderbuffer(target,renderbuffer);
    doCommonGLCheck();
}


void if_glwrapper::glBindTexture (GLenum target, GLuint texture)
{
   ::glBindTexture(target,texture);
    doCommonGLCheck();
}


void if_glwrapper::glBlendColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
   ::glBlendColor(red,green,blue,alpha);
    doCommonGLCheck();
}


void if_glwrapper::glBlendEquation ( GLenum mode )
{
   ::glBlendEquation(mode);
    doCommonGLCheck();
}


void if_glwrapper::glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha)
{
   ::glBlendEquationSeparate(modeRGB,modeAlpha);
    doCommonGLCheck();
}


void if_glwrapper::glBlendFunc (GLenum sfactor, GLenum dfactor)
{
   ::glBlendFunc(sfactor,dfactor);
    doCommonGLCheck();
}


void if_glwrapper::glBlendFuncSeparate (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
   ::glBlendFuncSeparate(srcRGB,dstRGB,srcAlpha,dstAlpha);
    doCommonGLCheck();
}


void if_glwrapper::glBufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
   ::glBufferData(target,size,data,usage);
    doCommonGLCheck();
}


void if_glwrapper::glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
{
   ::glBufferSubData(target,offset,size,data);
    doCommonGLCheck();
}


GLenum if_glwrapper::glCheckFramebufferStatus (GLenum target)
{
   GLenum ret =
   ::glCheckFramebufferStatus(target);
    doCommonGLCheck();
    return ret;
}


void if_glwrapper::glClear (GLbitfield mask)
{
   ::glClear(mask);
    doCommonGLCheck();
}


void if_glwrapper::glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
   ::glClearColor(red,green,blue,alpha);
    doCommonGLCheck();
}


void if_glwrapper::glClearDepthf (GLclampf depth)
{
   ::glClearDepthf(depth);
    doCommonGLCheck();
}


void if_glwrapper::glClearStencil (GLint s)
{
   ::glClearStencil(s);
    doCommonGLCheck();
}


void if_glwrapper::glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
   ::glColorMask(red,green,blue,alpha);
    doCommonGLCheck();
}


void if_glwrapper::glCompileShader (GLuint shader)
{
   ::glCompileShader(shader);
    doCommonGLCheck();
}


void if_glwrapper::glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)
{
   ::glCompressedTexImage2D(target,level,internalformat,width,height,border,imageSize,data);
    doCommonGLCheck();
}


void if_glwrapper::glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)
{
   ::glCompressedTexSubImage2D(target,level,xoffset,yoffset,width,height,format,imageSize,data);
    doCommonGLCheck();
}


void if_glwrapper::glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
   ::glCopyTexImage2D(target,level,internalformat,x,y,width,height,border);
    doCommonGLCheck();
}


void if_glwrapper::glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
   ::glCopyTexSubImage2D(target,level,xoffset,yoffset,x,y,width,height);
    doCommonGLCheck();
}


GLuint if_glwrapper::glCreateProgram ()
{
   GLuint ret =
   ::glCreateProgram();
    doCommonGLCheck();
    return ret;
}


GLuint if_glwrapper::glCreateShader (GLenum type)
{
   GLuint ret =
   ::glCreateShader(type);
    doCommonGLCheck();
    return ret;
}


void if_glwrapper::glCullFace (GLenum mode)
{
   ::glCullFace(mode);
    doCommonGLCheck();
}


void if_glwrapper::glDeleteBuffers (GLsizei n, const GLuint* buffers)
{
   ::glDeleteBuffers(n,buffers);
    doCommonGLCheck();
}


void if_glwrapper::glDeleteFramebuffers (GLsizei n, const GLuint* framebuffers)
{
   ::glDeleteFramebuffers(n,framebuffers);
    doCommonGLCheck();
}


void if_glwrapper::glDeleteProgram (GLuint program)
{
   ::glDeleteProgram(program);
    doCommonGLCheck();
}


void if_glwrapper::glDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers)
{
   ::glDeleteRenderbuffers(n,renderbuffers);
    doCommonGLCheck();
}


void if_glwrapper::glDeleteShader (GLuint shader)
{
   ::glDeleteShader(shader);
    doCommonGLCheck();
}


void if_glwrapper::glDeleteTextures (GLsizei n, const GLuint* textures)
{
   ::glDeleteTextures(n,textures);
    doCommonGLCheck();
}


void if_glwrapper::glDepthFunc (GLenum func)
{
   ::glDepthFunc(func);
    doCommonGLCheck();
}


void if_glwrapper::glDepthMask (GLboolean flag)
{
   ::glDepthMask(flag);
    doCommonGLCheck();
}


void if_glwrapper::glDepthRangef (GLclampf zNear, GLclampf zFar)
{
   ::glDepthRangef(zNear,zFar);
    doCommonGLCheck();
}


void if_glwrapper::glDetachShader (GLuint program, GLuint shader)
{
   ::glDetachShader(program,shader);
    doCommonGLCheck();
}


void if_glwrapper::glDisable (GLenum cap)
{
   ::glDisable(cap);
    doCommonGLCheck();
}


void if_glwrapper::glDisableVertexAttribArray (GLuint index)
{
   ::glDisableVertexAttribArray(index);
    doCommonGLCheck();
}


void if_glwrapper::glDrawArrays (GLenum mode, GLint first, GLsizei count)
{
   ::glDrawArrays(mode,first,count);
    doCommonGLCheck();
}


void if_glwrapper::glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
   ::glDrawElements(mode,count,type,indices);
    doCommonGLCheck();
}


void if_glwrapper::glEnable (GLenum cap)
{
   ::glEnable(cap);
    doCommonGLCheck();
}


void if_glwrapper::glEnableVertexAttribArray (GLuint index)
{
   ::glEnableVertexAttribArray(index);
    doCommonGLCheck();
}


void if_glwrapper::glFinish ()
{
   ::glFinish();
    doCommonGLCheck();
}


void if_glwrapper::glFlush ()
{
   ::glFlush();
    doCommonGLCheck();
}


void if_glwrapper::glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
   ::glFramebufferRenderbuffer(target,attachment,renderbuffertarget,renderbuffer);
    doCommonGLCheck();
}


void if_glwrapper::glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
   ::glFramebufferTexture2D(target,attachment,textarget,texture,level);
    doCommonGLCheck();
}


void if_glwrapper::glFrontFace (GLenum mode)
{
   ::glFrontFace(mode);
    doCommonGLCheck();
}


void if_glwrapper::glGenBuffers (GLsizei n, GLuint* buffers)
{
   ::glGenBuffers(n,buffers);
    doCommonGLCheck();
}


void if_glwrapper::glGenerateMipmap (GLenum target)
{
   ::glGenerateMipmap(target);
    doCommonGLCheck();
}


void if_glwrapper::glGenFramebuffers (GLsizei n, GLuint* framebuffers)
{
   ::glGenFramebuffers(n,framebuffers);
    doCommonGLCheck();
}


void if_glwrapper::glGenRenderbuffers (GLsizei n, GLuint* renderbuffers)
{
   ::glGenRenderbuffers(n,renderbuffers);
    doCommonGLCheck();
}


void if_glwrapper::glGenTextures (GLsizei n, GLuint* textures)
{
   ::glGenTextures(n,textures);
    doCommonGLCheck();
}


void if_glwrapper::glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
   ::glGetActiveAttrib(program,index,bufsize,length,size,type,name);
    doCommonGLCheck();
}


void if_glwrapper::glGetActiveUniform (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
   ::glGetActiveUniform(program,index,bufsize,length,size,type,name);
    doCommonGLCheck();
}


void if_glwrapper::glGetAttachedShaders (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
   ::glGetAttachedShaders(program,maxcount,count,shaders);
    doCommonGLCheck();
}


GLint if_glwrapper::glGetAttribLocation (GLuint program, const GLchar* name)
{
   GLint ret =
   ::glGetAttribLocation(program,name);
    doCommonGLCheck();
    return ret;
}


void if_glwrapper::glGetBooleanv (GLenum pname, GLboolean* params)
{
   ::glGetBooleanv(pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetBufferParameteriv (GLenum target, GLenum pname, GLint* params)
{
   ::glGetBufferParameteriv(target,pname,params);
    doCommonGLCheck();
}


GLenum if_glwrapper::glGetError ()
{
   GLenum ret =
   ::glGetError();
    doCommonGLCheck();
    return ret;
}


void if_glwrapper::glGetFloatv (GLenum pname, GLfloat* params)
{
   ::glGetFloatv(pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
   ::glGetFramebufferAttachmentParameteriv(target,attachment,pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetIntegerv (GLenum pname, GLint* params)
{
   ::glGetIntegerv(pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetProgramiv (GLuint program, GLenum pname, GLint* params)
{
   ::glGetProgramiv(program,pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
   ::glGetProgramInfoLog(program,bufsize,length,infolog);
    doCommonGLCheck();
}


void if_glwrapper::glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint* params)
{
   ::glGetRenderbufferParameteriv(target,pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetShaderiv (GLuint shader, GLenum pname, GLint* params)
{
   ::glGetShaderiv(shader,pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetShaderInfoLog (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
   ::glGetShaderInfoLog(shader,bufsize,length,infolog);
    doCommonGLCheck();
}


void if_glwrapper::glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
   ::glGetShaderPrecisionFormat(shadertype,precisiontype,range,precision);
    doCommonGLCheck();
}


void if_glwrapper::glGetShaderSource (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)
{
   ::glGetShaderSource(shader,bufsize,length,source);
    doCommonGLCheck();
}


const GLubyte* if_glwrapper::glGetString (GLenum name)
{
   const GLubyte* ret =
   ::glGetString(name);
    doCommonGLCheck();
    return ret;
}


void if_glwrapper::glGetTexParameterfv (GLenum target, GLenum pname, GLfloat* params)
{
   ::glGetTexParameterfv(target,pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetTexParameteriv (GLenum target, GLenum pname, GLint* params)
{
   ::glGetTexParameteriv(target,pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetUniformfv (GLuint program, GLint location, GLfloat* params)
{
   ::glGetUniformfv(program,location,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetUniformiv (GLuint program, GLint location, GLint* params)
{
   ::glGetUniformiv(program,location,params);
    doCommonGLCheck();
}


GLint if_glwrapper::glGetUniformLocation (GLuint program, const GLchar* name)
{
   GLint ret =
   ::glGetUniformLocation(program,name);
    doCommonGLCheck();
    return ret;
}


void if_glwrapper::glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat* params)
{
   ::glGetVertexAttribfv(index,pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetVertexAttribiv (GLuint index, GLenum pname, GLint* params)
{
   ::glGetVertexAttribiv(index,pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glGetVertexAttribPointerv (GLuint index, GLenum pname, GLvoid** pointer)
{
   ::glGetVertexAttribPointerv(index,pname,pointer);
    doCommonGLCheck();
}


void if_glwrapper::glHint (GLenum target, GLenum mode)
{
   ::glHint(target,mode);
    doCommonGLCheck();
}


GLboolean if_glwrapper::glIsBuffer (GLuint buffer)
{
   GLboolean ret =
   ::glIsBuffer(buffer);
    doCommonGLCheck();
    return ret;
}


GLboolean if_glwrapper::glIsEnabled (GLenum cap)
{
   GLboolean ret =
   ::glIsEnabled(cap);
    doCommonGLCheck();
    return ret;
}


GLboolean if_glwrapper::glIsFramebuffer (GLuint framebuffer)
{
   GLboolean ret =
   ::glIsFramebuffer(framebuffer);
    doCommonGLCheck();
    return ret;
}


GLboolean if_glwrapper::glIsProgram (GLuint program)
{
   GLboolean ret =
   ::glIsProgram(program);
    doCommonGLCheck();
    return ret;
}


GLboolean if_glwrapper::glIsRenderbuffer (GLuint renderbuffer)
{
   GLboolean ret =
   ::glIsRenderbuffer(renderbuffer);
    doCommonGLCheck();
    return ret;
}


GLboolean if_glwrapper::glIsShader (GLuint shader)
{
   GLboolean ret =
   ::glIsShader(shader);
    doCommonGLCheck();
    return ret;
}


GLboolean if_glwrapper::glIsTexture (GLuint texture)
{
   GLboolean ret =
   ::glIsTexture(texture);
    doCommonGLCheck();
    return ret;
}


void if_glwrapper::glLineWidth (GLfloat width)
{
   ::glLineWidth(width);
    doCommonGLCheck();
}


void if_glwrapper::glLinkProgram (GLuint program)
{
   ::glLinkProgram(program);
    doCommonGLCheck();
}


void if_glwrapper::glPixelStorei (GLenum pname, GLint param)
{
   ::glPixelStorei(pname,param);
    doCommonGLCheck();
}


void if_glwrapper::glPolygonOffset (GLfloat factor, GLfloat units)
{
   ::glPolygonOffset(factor,units);
    doCommonGLCheck();
}


void if_glwrapper::glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)
{
   ::glReadPixels(x,y,width,height,format,type,pixels);
    doCommonGLCheck();
}


void if_glwrapper::glReleaseShaderCompiler ()
{
   ::glReleaseShaderCompiler();
    doCommonGLCheck();
}


void if_glwrapper::glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
   ::glRenderbufferStorage(target,internalformat,width,height);
    doCommonGLCheck();
}


void if_glwrapper::glSampleCoverage (GLclampf value, GLboolean invert)
{
   ::glSampleCoverage(value,invert);
    doCommonGLCheck();
}


void if_glwrapper::glScissor (GLint x, GLint y, GLsizei width, GLsizei height)
{
   ::glScissor(x,y,width,height);
    doCommonGLCheck();
}


void if_glwrapper::glShaderBinary (GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)
{
   ::glShaderBinary(n,shaders,binaryformat,binary,length);
    doCommonGLCheck();
}


void if_glwrapper::glShaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint* length)
{
   ::glShaderSource(shader,count,string,length);
    doCommonGLCheck();
}


void if_glwrapper::glStencilFunc (GLenum func, GLint ref, GLuint mask)
{
   ::glStencilFunc(func,ref,mask);
    doCommonGLCheck();
}


void if_glwrapper::glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask)
{
   ::glStencilFuncSeparate(face,func,ref,mask);
    doCommonGLCheck();
}


void if_glwrapper::glStencilMask (GLuint mask)
{
   ::glStencilMask(mask);
    doCommonGLCheck();
}


void if_glwrapper::glStencilMaskSeparate (GLenum face, GLuint mask)
{
   ::glStencilMaskSeparate(face,mask);
    doCommonGLCheck();
}


void if_glwrapper::glStencilOp (GLenum fail, GLenum zfail, GLenum zpass)
{
   ::glStencilOp(fail,zfail,zpass);
    doCommonGLCheck();
}


void if_glwrapper::glStencilOpSeparate (GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
   ::glStencilOpSeparate(face,fail,zfail,zpass);
    doCommonGLCheck();
}


void if_glwrapper::glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
   ::glTexImage2D(target,level,internalformat,width,height,border,format,type,pixels);
    doCommonGLCheck();
}


void if_glwrapper::glTexParameterf (GLenum target, GLenum pname, GLfloat param)
{
   ::glTexParameterf(target,pname,param);
    doCommonGLCheck();
}


void if_glwrapper::glTexParameterfv (GLenum target, GLenum pname, const GLfloat* params)
{
   ::glTexParameterfv(target,pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glTexParameteri (GLenum target, GLenum pname, GLint param)
{
   ::glTexParameteri(target,pname,param);
    doCommonGLCheck();
}


void if_glwrapper::glTexParameteriv (GLenum target, GLenum pname, const GLint* params)
{
   ::glTexParameteriv(target,pname,params);
    doCommonGLCheck();
}


void if_glwrapper::glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)
{
   ::glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,pixels);
    doCommonGLCheck();
}


void if_glwrapper::glUniform1f (GLint location, GLfloat x)
{
   ::glUniform1f(location,x);
    doCommonGLCheck();
}


void if_glwrapper::glUniform1fv (GLint location, GLsizei count, const GLfloat* v)
{
   ::glUniform1fv(location,count,v);
    doCommonGLCheck();
}


void if_glwrapper::glUniform1i (GLint location, GLint x)
{
   ::glUniform1i(location,x);
    doCommonGLCheck();
}


void if_glwrapper::glUniform1iv (GLint location, GLsizei count, const GLint* v)
{
   ::glUniform1iv(location,count,v);
    doCommonGLCheck();
}


void if_glwrapper::glUniform2f (GLint location, GLfloat x, GLfloat y)
{
   ::glUniform2f(location,x,y);
    doCommonGLCheck();
}


void if_glwrapper::glUniform2fv (GLint location, GLsizei count, const GLfloat* v)
{
   ::glUniform2fv(location,count,v);
    doCommonGLCheck();
}


void if_glwrapper::glUniform2i (GLint location, GLint x, GLint y)
{
   ::glUniform2i(location,x,y);
    doCommonGLCheck();
}


void if_glwrapper::glUniform2iv (GLint location, GLsizei count, const GLint* v)
{
   ::glUniform2iv(location,count,v);
    doCommonGLCheck();
}


void if_glwrapper::glUniform3f (GLint location, GLfloat x, GLfloat y, GLfloat z)
{
   ::glUniform3f(location,x,y,z);
    doCommonGLCheck();
}


void if_glwrapper::glUniform3fv (GLint location, GLsizei count, const GLfloat* v)
{
   ::glUniform3fv(location,count,v);
    doCommonGLCheck();
}


void if_glwrapper::glUniform3i (GLint location, GLint x, GLint y, GLint z)
{
   ::glUniform3i(location,x,y,z);
    doCommonGLCheck();
}


void if_glwrapper::glUniform3iv (GLint location, GLsizei count, const GLint* v)
{
   ::glUniform3iv(location,count,v);
    doCommonGLCheck();
}


void if_glwrapper::glUniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
   ::glUniform4f(location,x,y,z,w);
    doCommonGLCheck();
}


void if_glwrapper::glUniform4fv (GLint location, GLsizei count, const GLfloat* v)
{
   ::glUniform4fv(location,count,v);
    doCommonGLCheck();
}


void if_glwrapper::glUniform4i (GLint location, GLint x, GLint y, GLint z, GLint w)
{
   ::glUniform4i(location,x,y,z,w);
    doCommonGLCheck();
}


void if_glwrapper::glUniform4iv (GLint location, GLsizei count, const GLint* v)
{
   ::glUniform4iv(location,count,v);
    doCommonGLCheck();
}


void if_glwrapper::glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
   ::glUniformMatrix2fv(location,count,transpose,value);
    doCommonGLCheck();
}


void if_glwrapper::glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
   ::glUniformMatrix3fv(location,count,transpose,value);
    doCommonGLCheck();
}


void if_glwrapper::glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
   ::glUniformMatrix4fv(location,count,transpose,value);
    doCommonGLCheck();
}


void if_glwrapper::glUseProgram (GLuint program)
{
   ::glUseProgram(program);
    doCommonGLCheck();
}


void if_glwrapper::glValidateProgram (GLuint program)
{
   ::glValidateProgram(program);
    doCommonGLCheck();
}


void if_glwrapper::glVertexAttrib1f (GLuint indx, GLfloat x)
{
   ::glVertexAttrib1f(indx,x);
    doCommonGLCheck();
}


void if_glwrapper::glVertexAttrib1fv (GLuint indx, const GLfloat* values)
{
   ::glVertexAttrib1fv(indx,values);
    doCommonGLCheck();
}


void if_glwrapper::glVertexAttrib2f (GLuint indx, GLfloat x, GLfloat y)
{
   ::glVertexAttrib2f(indx,x,y);
    doCommonGLCheck();
}


void if_glwrapper::glVertexAttrib2fv (GLuint indx, const GLfloat* values)
{
   ::glVertexAttrib2fv(indx,values);
    doCommonGLCheck();
}


void if_glwrapper::glVertexAttrib3f (GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{
   ::glVertexAttrib3f(indx,x,y,z);
    doCommonGLCheck();
}


void if_glwrapper::glVertexAttrib3fv (GLuint indx, const GLfloat* values)
{
   ::glVertexAttrib3fv(indx,values);
    doCommonGLCheck();
}


void if_glwrapper::glVertexAttrib4f (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
   ::glVertexAttrib4f(indx,x,y,z,w);
    doCommonGLCheck();
}


void if_glwrapper::glVertexAttrib4fv (GLuint indx, const GLfloat* values)
{
   ::glVertexAttrib4fv(indx,values);
    doCommonGLCheck();
}


void if_glwrapper::glVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{
   ::glVertexAttribPointer(indx,size,type,normalized,stride,ptr);
    doCommonGLCheck();
}


void if_glwrapper::glViewport (GLint x, GLint y, GLsizei width, GLsizei height)
{
   ::glViewport(x,y,width,height);
    doCommonGLCheck();
}


