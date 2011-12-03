//
//  main.cpp
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-11-30.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#define kOutputFile "/Users/drakej/Desktop/test_image.jpg"

#include <iostream>         // for error output
#include <vector>

#include <OpenGL/gl3.h>


#include "Context.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "RenderBuffer.h"

//#include "iso.h"


/*
    Notes:
        Original code used NSOpenGLContext 
            -> converted to CGL
        Original code checks for the frame buffer object 
            -> the idea is to convert this code to OpenGL 3.2, so we don't test for it anymore
            -> side effect, we don't need glu* (or not) anymore, and now get rid of EXT on functions
 */
int main (int argc, char * const argv[])
{
    
    /*
     * Create an OpenGL context just so that OpenGL calls will work. I'm not using it for actual rendering.
     */
    GLContext context;
    context.makeCurrent();
    context.renderInfo();
    
    if (argc == 1) 
    {
        std::cout << "No shader path found." << std::endl;
        return 1;
    }
    
    std::string path = argv[1]; std::cout << "Shader path: " << path << std::endl;
    
    RenderBuffer render(128, 128, true); // use a buffer with depth
    render.use();

    context.addShader("basic", "basic.vsh", "basic.fsh");
    context.ortho(-render.width()/2.0f, render.width() / 2.0f, -render.height() / 2.0f, render.height() / 2.0f, -1.0f, 1.0f);
    context.useShader("basic");

    glm::vec4 stuff[] = { glm::vec4(0.0f, 60.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
         glm::vec4(40.0f, -40.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
         glm::vec4(-40.0f, -40.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) };
    
    VertexBuffer vertices;
    vertices.buffer(6, stuff);
    
    context.depthTest(true);
    context.clearColour(glm::vec4(0.0, 0.0, 0.0, 1.0));
    context.viewport(0, 0, render.width(), render.height());
    context.clearColourBuffer();
    context.clearDepthBuffer();
    
    vertices.enableLocation(0, 0, 2);
    vertices.enableLocation(1, 1, 2);
    vertices.drawTriangles(0, 3);
    
    glFinish();
    REPORTGLERROR("glFinish()");

    render.image();
    
    context.clearDrawable();
    
    return 0;
}

