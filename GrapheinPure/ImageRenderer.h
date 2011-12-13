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

class ImageRenderer
{
    GLuint  renderBuffer = 0;
    GLuint  depthBuffer = 0;
    GLuint  frameBuffer = 0;
    int _width = 128, _height = 128;


public:
    ImageRenderer() = default;
    ImageRenderer(int width, int height, bool depth = false);
    
    int save(const char *file);
    
    int width() { return _width; }
    int height() { return _height; }
    
    // these should be transparent
    void use();
    void unuse();

};

#endif
