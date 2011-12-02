//
//  RenderBuffer.h
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-12-02.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GrapheinPure_RenderBuffer_h
#define GrapheinPure_RenderBuffer_h

#include <OpenGL/gl3.h>

class RenderBuffer
{
    GLuint  renderBuffer = 0;
    GLuint  depthBuffer = 0;
    GLuint  frameBuffer = 0;
    int _width = 128, _height = 128;
    
public:
    RenderBuffer() = default;
    RenderBuffer(int width, int height, bool depth = false);
    
    void use();
    void unuse();
    void image();
    
    int width() { return _width; }
    int height() { return _height; }
};

#endif
