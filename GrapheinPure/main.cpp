//
//  main.cpp
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-11-30.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

//#include <iostream>
//#include <OpenGL/gl3.h>
//#include <OpenGL/OpenGL.h>

//using namespace std;
/*
int main (int argc, const char * argv[])
{

    // insert code here...
//    std::cout << "Hello, World!\n";
    CGLError err;
    
    CGLPixelFormatAttribute format[] = {
        kCGLPFAAllowOfflineRenderers,
        kCGLPFAOpenGLProfile, (CGLPixelFormatAttribute)kCGLOGLPVersion_3_2_Core,
        kCGLPFAAccelerated,
        (CGLPixelFormatAttribute)0
    };
    
    CGLPixelFormatObj pix;
    GLint p = 0;
    
    err = CGLChoosePixelFormat(format, &pix, &p);
    
    if (err)
    {
        cout << CGLErrorString(err) << endl;
        return 1;
    }
    
    cout << "Screens: " << p << endl;
    cout << "Pixel Format null? " << (pix == NULL ? "yes" : "no") << endl;
    
    CGLContextObj context;
    
    err = CGLCreateContext(pix, NULL, &context);
    
    if (err)
    {
        cout << CGLErrorString(err) << endl;
        return 1;
    }

    cout << "Context null? " << (pix == NULL ? "yes" : "no") << endl;
    
    
    
    return 0;
}*/

#define kOutputFile "/Users/drakej/Desktop/test_image.jpg"

#include <iostream>         // for error output
#import <OpenGL/OpenGL.h>
#import <OpenGL/glu.h>      // for gluCheckExtension
#include <ApplicationServices/ApplicationServices.h> //CGColorSpace.h
//#import <AppKit/AppKit.h>   // for NSOpenGL...

// Simple error reporting macros to help keep the sample code clean
#define REPORTGLERROR(task) { GLenum tGLErr = glGetError(); if (tGLErr != GL_NO_ERROR) { std::cout << "OpenGL error " << tGLErr << " while " << task << "\n"; } }
#define REPORT_ERROR_AND_EXIT(desc) { std::cout << desc << "\n"; return 1; }
#define NULL_ERROR_EXIT(test, desc) { if (!test) REPORT_ERROR_AND_EXIT(desc); }

int main (int argc, char * const argv[])
{
//	NSAutoreleasePool*			pool = [NSAutoreleasePool new];
    
    /*
     * Create an OpenGL context just so that OpenGL calls will work. I'm not using it for actual rendering.
     */
    
    
    CGLError err;
    
    CGLPixelFormatAttribute format[] = {
        kCGLPFAPBuffer, // obsolete
        kCGLPFANoRecovery, 
        kCGLPFAAccelerated,
        kCGLPFADepthSize, (CGLPixelFormatAttribute)24,
        (CGLPixelFormatAttribute)0
    };
    
    CGLPixelFormatObj pix;
    GLint p = 0;

    err = CGLChoosePixelFormat(format, &pix, &p);

    if (err)
    {
        std::cout << CGLErrorString(err) << std::endl;
        return 1;
    }
    
    CGLPBufferObj pixBuf;
    
    err = CGLCreatePBuffer(32, 32, GL_TEXTURE_RECTANGLE_EXT, GL_RGBA , 0, &pixBuf);

    /*
	NSOpenGLPixelBuffer*		pixBuf;
	NSOpenGLContext*			openGLContext;
	NSOpenGLPixelFormatAttribute	attributes[] = {
        NSOpenGLPFAPixelBuffer,
        NSOpenGLPFANoRecovery,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADepthSize, 24,
        (NSOpenGLPixelFormatAttribute) 0
    };
	NSOpenGLPixelFormat*		pixFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attributes] autorelease];
	
    // Create an OpenGL pixel buffer
    pixBuf = [[NSOpenGLPixelBuffer alloc] initWithTextureTarget:GL_TEXTURE_RECTANGLE_EXT textureInternalFormat:GL_RGBA textureMaxMipMapLevel:0 pixelsWide:32 pixelsHigh:32]; */
    NULL_ERROR_EXIT(pixBuf, "Unable to create NSOpenGLPixelBuffer");
    
    CGLContextObj openGLContext;
    
    err = CGLCreateContext(pix, NULL, &openGLContext);
    if (err)
    {
        std::cout << CGLErrorString(err) << std::endl;
        return 1;
    }
    
    // Create the OpenGL context to render with (with color and depth buffers)
    //openGLContext = [[NSOpenGLContext alloc] initWithFormat:pixFormat shareContext:nil];
    NULL_ERROR_EXIT(openGLContext, "Unable to create NSOpenGLContext");
    
    GLint screen;
    
    err = CGLGetVirtualScreen(openGLContext, &screen);
    if (err)
    {
        std::cout << CGLErrorString(err) << std::endl;
        return 1;
    }
    
    
    err = CGLSetPBuffer(openGLContext, pixBuf, 0, 0, screen);
    if (err)
    {
        std::cout << CGLErrorString(err) << std::endl;
        return 1;
    }
/*    [openGLContext setPixelBuffer:pixBuf cubeMapFace:0 mipMapLevel:0 currentVirtualScreen:[openGLContext currentVirtualScreen]]; */
    CGLSetCurrentContext(openGLContext);
//    [openGLContext makeCurrentContext];
    
    /*
     * Test if framebuffer objects are supported
     */
    
    const GLubyte* strExt = glGetString(GL_EXTENSIONS);
    GLboolean fboSupported = gluCheckExtension((const GLubyte*)"GL_EXT_framebuffer_object", strExt);
    if (!fboSupported)
        REPORT_ERROR_AND_EXIT("Your system does not support framebuffer extension - unable to render scene");
    
    /*
     * Create an FBO
     */
    
    GLuint  renderBuffer = 0;
    GLuint  depthBuffer = 0;
    int     img_width = 128, img_height = 128; // <-- pixel size of the rendered scene - hardcoded values for testing
    
    // Depth buffer to use for depth testing - optional if you're not using depth testing
    glGenRenderbuffersEXT(1, &depthBuffer);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthBuffer);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, img_width, img_height);
    REPORTGLERROR("creating depth render buffer");
    
    // Render buffer to use for imaging
    glGenRenderbuffersEXT(1, &renderBuffer);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderBuffer);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA8, img_width, img_height);
    REPORTGLERROR("creating color render buffer");
    
    GLuint  fbo = 0;
    glGenFramebuffersEXT(1, &fbo);
    
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    REPORTGLERROR("binding framebuffer");
    
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, renderBuffer);
    REPORTGLERROR("specifying color render buffer");
    
    if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
        REPORT_ERROR_AND_EXIT("Problem with OpenGL framebuffer after specifying color render buffer.");
    
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthBuffer);
    REPORTGLERROR("specifying depth render buffer");
    
    if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
        REPORT_ERROR_AND_EXIT("Problem with OpenGL framebuffer after specifying depth render buffer.");
    
    /*
     * Render a simple shape to the FBO
     */
    
    glEnable(GL_DEPTH_TEST);
    REPORTGLERROR("enabling depth testing");
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    REPORTGLERROR("specifying clear color");
    
    glViewport(0, 0, img_width, img_height);
    REPORTGLERROR("specifying viewport");
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-img_width / 2, img_width / 2, -img_height / 2, img_height / 2, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    REPORTGLERROR("setting up view/model matrices");
    
    glClear(GL_COLOR_BUFFER_BIT);
    REPORTGLERROR("clearing color buffer");
    
    glClear(GL_DEPTH_BUFFER_BIT);
    REPORTGLERROR("clearing depth buffer");
    
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 60.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(40.0, -40.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-40.0, -40.0, 0.0);
    glEnd();
    REPORTGLERROR("rendering scene");
    
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
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    
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
    
//    [openGLContext clearDrawable];
    err = CGLClearDrawable(openGLContext);
    if (err)
    {
        std::cout << CGLErrorString(err) << std::endl;
        return 1;
    }

    
//    [openGLContext release];
    err = CGLDestroyContext(openGLContext);
    if (err)
    {
        std::cout << CGLErrorString(err) << std::endl;
        return 1;
    }

    
    //[pixBuf release];
    err = CGLDestroyPBuffer(pixBuf);
    
//	[pool release];
    
    return 0;
}
