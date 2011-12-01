//
//  Context.h
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-11-30.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GrapheinPure_Context_h
#define GrapheinPure_Context_h

#include <OpenGL/OpenGL.h>
#include <iostream>
#include <string>
#include <map>

#include "Shader.h"

// Simple error reporting macros to help keep the sample code clean
#define REPORTGLERROR(task) { GLenum tGLErr = glGetError(); if (tGLErr != GL_NO_ERROR) { std::cout << "OpenGL error " << tGLErr << " while " << task << "\n"; } }
#define REPORT_ERROR_AND_EXIT(desc) { std::cout << desc << "\n"; return 1; }
#define REPORT_ERROR_AND_THROW(desc) { std::cout << desc << "\n"; throw std::string(desc); }
#define NULL_ERROR_EXIT(test, desc) { if (!test) REPORT_ERROR_AND_EXIT(desc); }
#define NULL_ERROR_THROW(test, desc) { if (!test) REPORT_ERROR_AND_THROW(desc); }

#define CATCH_GL_ERROR(error) { if (error) { std::cout << CGLErrorString(err) << std::endl; throw std::string(CGLErrorString(err)); } }

class GLContext
{
    CGLContextObj context;
    std::map<std::string, Shader> shaders;
    glm::mat4 projection;
    glm::mat4 modelview;
    
public:
    GLContext();
    ~GLContext();
    void makeCurrent();
    void clearDrawable();
    void renderInfo();
    
    void addShader(std::string name, std::string vertexFile, std::string fragmentFile);
    bool setUniform(const std::string name, const std::string uniformName, const glm::mat4 &matrix);
    void useShader(std::string name);
    
    void ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    
    void clearColour(const glm::vec4 &c);

    void clearColourBuffer();
    void clearDepthBuffer();
    
    bool depthTest(bool enable);
    bool depthTest();
    
    void viewport(int left, int top, int width, int height);
    
    
};

#endif
