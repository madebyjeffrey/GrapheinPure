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

#include "iso.h"

int main (int argc, char * const argv[])
{

    GLContext context;
    context.makeCurrent();
    context.renderInfo();
    
    if (argc == 1) 
    {
        std::cout << "No shader path found." << std::endl;
        return 1;
    }
    
    std::string path = argv[1]; std::cout << "Shader path: " << path << std::endl;
    
    RenderBuffer render(512, 512, true); // use a buffer with depth
    render.use();

    context.addShader("basic", "basic.vsh", "basic.fsh");
    context.ortho(-render.width()/2.0f, render.width() / 2.0f, -render.height() / 2.0f, render.height() / 2.0f, -1.0f, 1.0f);
    context.useShader("basic");

    using namespace iso;
    
    auto vertices = context.newVertexBuffer()
        << (vec4){0.0f, 60.0f, 0.0f, 1.0f}
        << (vec4){1.0f, 0.0f, 0.0f, 1.0f}
        << (vec4){40.0f, -40.0f, 0.0f, 1.0f}
        << (vec4){0.0f, 1.0f, 0.0f, 1.0f}
        << (vec4){-40.0f, -40.0f, 0.0f, 1.0f}
        << (vec4){0.0f, 0.0f, 1.0f, 1.0f}
        << commit;
    
    /*
    context 
        << enableDepthTest
        << clearColour(BLACK)
        << viewport(0, 0, render.width(), render.height())
        << clearColourbuffer
        << clearDepthBuffer;
    
    if (context.fail())
        abort();

    vertices.drawTriangles(0, 3);
    context.finish(); */
    
    
    context.depthTest(true);
    context.clearColour((iso::vec4){0.0, 0.0, 0.0, 1.0});
    context.viewport(0, 0, render.width(), render.height());
    context.clearColourBuffer();
    context.clearDepthBuffer();
    
   // vertices.enableLocation(0, 0, 2);
//    vertices.enableLocation(1, 1, 2);
    vertices.drawTriangles(0, 3);
    
    context.finish();

    render.image();
    
    context.clearDrawable();
    
    return 0;
}

