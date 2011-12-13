//
//  Context.cpp
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-11-30.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include <OpenGL/gl3.h>

#include "Context.h"


void GLContext::fatalCGError(GLError error, CGLError err) 
{
    if (err == kCGLNoError) return;
    
    std::string errstr = CGLErrorString(err);
    errorNumber = error;
    errorString = errstr;
    
    throw std::runtime_error(errorString);
}

void GLContext::testCGError(GLError error, CGLError err) 
{
    if (err == kCGLNoError) return;
    
    std::string errstr = CGLErrorString(err);
    errorNumber = error;
    errorString = errstr;
}

void GLContext::testGLError(GLError error, const char *estr) 
{
    std::string errstr = estr;
    
    GLenum tGLErr = glGetError(); 
    if (tGLErr != GL_NO_ERROR) 
    { 
        errorNumber = error;
        errorString = errstr;
    }
}


GLContext::GLContext() : context(NULL)
{
    CGLError err;
    
    CGLPixelFormatAttribute format[] = {
//        kCGLPFAPBuffer, // obsolete
        kCGLPFANoRecovery, 
        kCGLPFAAccelerated,
        kCGLPFADepthSize, (CGLPixelFormatAttribute)24,
        kCGLPFAOpenGLProfile, (CGLPixelFormatAttribute)kCGLOGLPVersion_3_2_Core,
        (CGLPixelFormatAttribute)0
    };
    
    CGLPixelFormatObj pix;
    GLint p = 0;
    
    err = CGLChoosePixelFormat(format, &pix, &p);
    fatalCGError(GLError::PixelFormatError, err);
    
    err = CGLCreateContext(pix, NULL, &context);
    fatalCGError(GLError::ContextCreationError, err);
}

GLContext::~GLContext()
{
    CGLError err = CGLDestroyContext(context);
    fatalCGError(GLError::ContextDestructionError, err);
}

void GLContext::makeCurrent()
{
    CGLError err = CGLSetCurrentContext(context);
    testCGError(GLError::ContextSetError, err);
}

void GLContext::clearDrawable()
{
    CGLError err = CGLClearDrawable(context);
    testCGError(GLError::ClearDrawableError, err);
}

void GLContext::renderInfo()
{
	std::cout << "OpenGL Rendering Info" << std::endl;

	if (glGetString(GL_VENDOR) == NULL) 
	{
		std::cout << "No Vendor String" << std::endl;
        
		return;
	}
	
	std::cout << "Vendor:" << glGetString(GL_VENDOR) << std::endl;
    testGLError(GLError::GetStringError, "Get vendor string");

	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    testGLError(GLError::GetStringError, "Get Renderer string");
    
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    testGLError(GLError::GetStringError, "Get Version String");
    
	std::cout << "Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;
    testGLError(GLError::GetStringError, "Get shading language version");
}

void GLContext::addShader(std::string name, std::string vertexFile, std::string fragmentFile)
{
    Shader s;
    s.compile(fragmentFile, GL_FRAGMENT_SHADER);
    s.compile(vertexFile, GL_VERTEX_SHADER);
    s.link();
    s.use();
    
    shaders[name] = s;
}

bool GLContext::setUniform(const std::string name, const std::string uniformName, const iso::mat4 &matrix)
{
    return shaders[name].setUniform(uniformName, matrix);
}

void GLContext::useShader(std::string name)
{
    shaders[name].use();
    
    setUniform(name, "ProjectionMatrix", projection);
}

void GLContext::ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
    projection = iso::ortho2d(left, right, bottom, top, zNear, zFar);
}

void GLContext::clearColour(const iso::vec4 &c)
{
    glClearColor(c[0], c[1], c[2], c[3]);
    testGLError(GLError::ClearColourError, "specifying clear color");
}

bool GLContext::depthTest(bool enable)
{
    GLboolean v = glIsEnabled(GL_DEPTH_TEST);
    testGLError(GLError::DepthTestError, "is depth testing enabled");
    if (enable)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
    
    testGLError(GLError::DepthTestError, "enabling/disabling depth testing");
    
    return v == GL_TRUE;
}

bool GLContext::depthTest()
{
    GLboolean v = glIsEnabled(GL_DEPTH_TEST);
    testGLError(GLError::DepthTestError, "is depth testing enabled");
    return v == GL_TRUE;    
}

void GLContext::viewport(int left, int top, int width, int height)
{
    glViewport(left, top, width, height);
    testGLError(GLError::ViewportError, "specifying viewport");
}

void GLContext::clearColourBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
    testGLError(GLError::ClearColourError, "clearing color buffer");
}

void GLContext::clearDepthBuffer()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    testGLError(GLError::DepthTestError, "clearing depth buffer");
}

void GLContext::finish()
{
    glFinish();
    testGLError(GLError::FinishError, "glFinish()");
}