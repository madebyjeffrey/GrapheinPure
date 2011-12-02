//
//  RenderBuffer.cpp
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-12-02.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include <boost/gil/gil_all.hpp>
// fix for libpng change that gil hasn't caught up with
#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL


#include <boost/gil/extension/io/png_io.hpp>

#include <OpenGL/gl3.h>

#include "RenderBuffer.h"
#include "Context.h"



RenderBuffer::RenderBuffer(int width, int height, bool depth) 
    : _width(width), _height(height)
{
    if (depth)
    {
	    glGenRenderbuffers(1, &depthBuffer);
        std::cout << "Depth Buffer: " << depthBuffer << std::endl;
        REPORTGLERROR("generate depth buffer");
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        REPORTGLERROR("bind render buffer to depth buffer");
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
        REPORTGLERROR("creating depth render buffer");
    }
    
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB8, width, height);
    REPORTGLERROR("creating color render buffer");    

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    REPORTGLERROR("binding framebuffer");
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer);
    REPORTGLERROR("specify colour buffer");
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    REPORTGLERROR("Problem with OpenGL framebuffer after specifying color render buffer.");
    
    if (depth)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        REPORTGLERROR("specifying depth render buffer");
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        REPORTGLERROR("Problem with OpenGL framebuffer after specifying depth render buffer.");
    }
}

void RenderBuffer::use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    REPORTGLERROR("binding framebuffer");

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        REPORTGLERROR("Problem with OpenGL framebuffer after specifying depth render buffer.");

}

void RenderBuffer::unuse()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderBuffer::image()
{
    using namespace boost::gil;
    
    const int samplesPerPixel = 4; // R, G, B and A
    const int rowBytes = samplesPerPixel * _width;
    char* bufferData = (char*)malloc(rowBytes * _height);
//    NULL_ERROR_EXIT(bufferData, "Unable to allocate buffer for image extraction.");


    REPORTGLERROR("reading pixels from framebuffer");
    
    

//    image<rgba8_pixel_t, false> buffer(_width, _height);
    glPixelStorei(GL_PACK_SWAP_BYTES, GL_FALSE);
    glPixelStorei(GL_PACK_LSB_FIRST, GL_FALSE);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    glReadPixels(0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, bufferData);
   
    rgba8_view_t img = interleaved_view(_width, _height, (rgba8_pixel_t*) bufferData, rowBytes);
    
//    copy_pixels(flipped_up_down_view(img), 
    png_write_view("/Users/drakej/Desktop/test_image.jpg", img);

}