//
//  Context.cpp
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-11-30.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <cstddef>
#include <iostream>

#include <OpenGL/gl3.h>

#include "Context.h"

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
    CATCH_GL_ERROR(err);

    err = CGLCreateContext(pix, NULL, &context);
    CATCH_GL_ERROR(err);
}

GLContext::~GLContext()
{
    CGLError err = CGLDestroyContext(context);
    CATCH_GL_ERROR(err);
}

void GLContext::makeCurrent()
{
    CGLError err = CGLSetCurrentContext(context);
    CATCH_GL_ERROR(err);
}

void GLContext::clearDrawable()
{
    CGLError err = CGLClearDrawable(context);
    CATCH_GL_ERROR(err);
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
    REPORTGLERROR("Get vendor string");

	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    REPORTGLERROR("Get Renderer string");
    
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    REPORTGLERROR("Get Version String");
    
	std::cout << "Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;
    REPORTGLERROR("Get shading language version");
}