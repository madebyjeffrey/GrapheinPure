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
#include "ImageRenderer.h"

#include "iso.h"
/*
std::ostream &operator<<(std::ostream &o, const iso::mat4 &m)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            o << "\t" << (m[i][j]);
        o << std::endl;
    }
    
    return o;
}*/


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
    
    ImageRenderer image(512, 512, true); // use a buffer with depth
    image.use();

    context.addShader("basic", "basic.vsh", "basic.fsh");
    context.ortho(-image.width()/2.0f, image.width() / 2.0f, -image.height() / 2.0f, image.height() / 2.0f, -1.0f, 1.0f);
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
    context.viewport(0, 0, image.width(), image.height());
    context.clearColourBuffer();
    context.clearDepthBuffer();
    
   // vertices.enableLocation(0, 0, 2);
//    vertices.enableLocation(1, 1, 2);
    vertices.drawTriangles(0, 3);
    
    context.finish();

    image.save("/Users/drakej/Desktop/test_image.jpg");
    
    context.clearDrawable();
    
    return 0;
}

