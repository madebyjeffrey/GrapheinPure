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

#include "glError.h"

#include "iso.h"

#include "Shader.h"
#include "VertexBuffer.h"

enum class GLError : std::int32_t 
{
    NoError,
    UndefinedError,
    PixelFormatError,
    ContextCreationError,
    ContextDestructionError,
    ContextSetError,
    ClearDrawableError,
    GetStringError,
    ClearColourError,
    DepthTestError,
    ViewportError,
    FinishError
};

class GLContext
{
    CGLContextObj context;
    std::map<std::string, Shader> shaders;
    iso::mat4 projection;
    iso::mat4 modelview;

    GLError errorNumber;
    std::string errorString;
    
    void fatalCGError(GLError error, CGLError err);
    void testCGError(GLError error, CGLError err);
    void testGLError(GLError error, const char *estr);
public:
    GLContext();
    ~GLContext();
    void makeCurrent();
    void clearDrawable();
    void renderInfo();
    
    void addShader(std::string name, std::string vertexFile, std::string fragmentFile);
    bool setUniform(const std::string name, const std::string uniformName, const iso::mat4 &matrix);
    void useShader(std::string name);
    
    void ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    
    void clearColour(const iso::vec4 &c);

    void clearColourBuffer();
    void clearDepthBuffer();
    
    bool depthTest(bool enable);
    bool depthTest();
    
    void viewport(int left, int top, int width, int height);
    
    void finish();
    
    void setError(GLError error, const char *text);
    
    /* Vertex Buffer */
    
    VertexBuffer<PCPacked> newVertexBuffer()
    {
        VertexBuffer<PCPacked> vb;
        return vb;
    }
};

#endif
