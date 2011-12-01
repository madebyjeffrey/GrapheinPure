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

#include <OpenGL/OpenGL.h>

#include <OpenGL/gl3.h>

//#include <OpenGL/glu.h>
//#include <OpenGL/glext.h>      
#include <ApplicationServices/ApplicationServices.h> //CGColorSpace.h

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include "Context.h"
#include "Shader.h"
#include "Buffer.h"

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
    
    /*
     * Create an FBO
     */
    
    GLuint  renderBuffer = 0;
    GLuint  depthBuffer = 0;
    int     img_width = 128, img_height = 128; // <-- pixel size of the rendered scene - hardcoded values for testing
    
    // Depth buffer to use for depth testing - optional if you're not using depth testing
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, img_width, img_height);
    REPORTGLERROR("creating depth render buffer");
    
    // Render buffer to use for imaging
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, img_width, img_height);
    REPORTGLERROR("creating color render buffer");
    
    GLuint  fbo = 0;
    glGenFramebuffers(1, &fbo);
    
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    REPORTGLERROR("binding framebuffer");
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer);
    REPORTGLERROR("specifying color render buffer");
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        REPORT_ERROR_AND_EXIT("Problem with OpenGL framebuffer after specifying color render buffer.");
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    REPORTGLERROR("specifying depth render buffer");
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        REPORT_ERROR_AND_EXIT("Problem with OpenGL framebuffer after specifying depth render buffer.");

    
    context.addShader("basic", "basic.vsh", "basic.fsh");
    context.ortho(-img_width/2.0f, img_width / 2.0f, -img_height / 2.0f, img_height / 2.0f, -1.0f, 1.0f);
    context.useShader("basic");
    
    GLuint arraybuffer[1]; 
    glGenBuffers(1, arraybuffer);
    
// std::vector<double> triangle ;
    
    glm::vec4 stuff[] = { glm::vec4(0.0f, 60.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
         glm::vec4(40.0f, -40.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
         glm::vec4(-40.0f, -40.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) };
    
    VertexBuffer vertices;
    vertices.buffer(6, stuff);
    
    /*
    struct vertex {
        glm::vec4 position;
        glm::vec4 colour;
    } triangle[] = { { glm::vec4(0.0f, 60.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
                     { glm::vec4(40.0f, -40.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },
                     { glm::vec4(-40.0f, -40.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }};

    
  //  cout << "Size of triangle: " << sizeof(position) << endl;
    glBindBuffer(GL_ARRAY_BUFFER, arraybuffer[0]);
    REPORTGLERROR("bound array buffer");
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), (GLvoid*)triangle, GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(position), (GLvoid*)position, GL_STATIC_DRAW);
    REPORTGLERROR("Buffer array data");
    */
    /*
     * Render a simple shape to the FBO
     */
    
    context.depthTest(true);
    context.clearColour(glm::vec4(0.0, 0.0, 0.0, 1.0));
    context.viewport(0, 0, img_width, img_height);
    context.clearColourBuffer();
    context.clearDepthBuffer();
    
    /*
    GLuint vao;
    glGenVertexArrays(1, &vao);
    REPORTGLERROR("gen vao");
    
    glBindVertexArray(vao);
    REPORTGLERROR("bind vao");
    
    glEnableVertexAttribArray(0);
    REPORTGLERROR("enable array 0");
    glEnableVertexAttribArray(1);
    REPORTGLERROR("enable array 1");
    
    */
    vertices.enableLocation(0, 0, 1);
    vertices.enableLocation(1, 1, 1);
    vertices.drawTriangles(0, 3);

//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, position));  
//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);  
//    REPORTGLERROR("tell it vertex data");
    
  //  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, colour));
//    REPORTGLERROR("tell it colour data");
    
//    s.validate();
//    REPORTGLERROR("Validate program");
    
  //  glDrawArrays(GL_TRIANGLES, 0, 3);
//    REPORTGLERROR("rendering scene");
    
    glFinish();
    REPORTGLERROR("glFinish()");

    
    /*
     * Extract the resulting rendering as an image
     */
    
    int samplesPerPixel = 4; // R, G, B and A
    int rowBytes = samplesPerPixel * img_width;
    char* bufferData = (char*)malloc(rowBytes * img_height);
    NULL_ERROR_EXIT(bufferData, "Unable to allocate buffer for image extraction.");
    
    glReadPixels(0, 0, img_width, img_height, GL_BGRA, GL_UNSIGNED_BYTE, bufferData);
    REPORTGLERROR("reading pixels from framebuffer");
    
    // Flip it vertically - images read from OpenGL buffers are upside-down
    char* flippedBuffer = (char*)malloc(rowBytes * img_height);
    NULL_ERROR_EXIT(flippedBuffer, "Unable to allocate flipped buffer for corrected image.");
    for (int i = 0 ; i < img_height ; i++)
    {
        bcopy(bufferData + i * rowBytes, flippedBuffer + (img_height - i - 1) * rowBytes, rowBytes);
    }
    
    // "un"bind my FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    /*
     * Output the image to a file
     */
    
	CGColorSpaceRef colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
    CGBitmapInfo bitmapInfo = kCGImageAlphaNoneSkipFirst | kCGBitmapByteOrder32Little;	// XRGB Little Endian
    int bitsPerComponent = 8;
    CGContextRef contextRef = CGBitmapContextCreate(flippedBuffer,
                                                    img_width, img_height, bitsPerComponent, rowBytes, colorSpace, bitmapInfo);
    NULL_ERROR_EXIT(contextRef, "Unable to create CGContextRef.");
    
    CGImageRef imageRef = CGBitmapContextCreateImage(contextRef);
    NULL_ERROR_EXIT(imageRef, "Unable to create CGImageRef.");
    
    Boolean isDirectory = false;
    CFURLRef fileURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
                                                     CFSTR(kOutputFile), kCFURLPOSIXPathStyle, isDirectory);
    NULL_ERROR_EXIT(fileURL, "Unable to create file URL ref.");
    
    CFIndex                 fileImageIndex = 1;
    CFMutableDictionaryRef  fileDict       = NULL;
    CFStringRef             fileUTType     = kUTTypeJPEG;
    
    // Create an image destination opaque reference for authoring an image file
    CGImageDestinationRef imageDest = CGImageDestinationCreateWithURL(fileURL, 
                                                                      fileUTType, 
                                                                      fileImageIndex, 
                                                                      fileDict);
    
    NULL_ERROR_EXIT(imageDest, "Unable to create CGImageDestinationRef.");
    
    CFIndex capacity = 1;
    CFMutableDictionaryRef imageProps = CFDictionaryCreateMutable(kCFAllocatorDefault, 
                                                                  capacity,
                                                                  &kCFTypeDictionaryKeyCallBacks,
                                                                  &kCFTypeDictionaryValueCallBacks);
    
    CGImageDestinationAddImage(imageDest, imageRef, imageProps);
    CGImageDestinationFinalize(imageDest);
    
    /*
     * Cleanup
     */
    
    free(flippedBuffer);
    free(bufferData);
    
    CFRelease(imageDest);
    CFRelease(fileURL);
    CFRelease(imageProps);
    CGColorSpaceRelease( colorSpace );
    CGImageRelease(imageRef);
    
    context.clearDrawable();
    
    return 0;
}

