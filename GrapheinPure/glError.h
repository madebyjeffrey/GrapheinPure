//
//  glError.h
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-12-06.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GrapheinPure_glError_h
#define GrapheinPure_glError_h

// Simple error reporting macros to help keep the sample code clean
#define REPORTGLERROR(task) { GLenum tGLErr = glGetError(); if (tGLErr != GL_NO_ERROR) { std::cout << "OpenGL error " << tGLErr << " while " << task << "\n"; } }
#define REPORT_ERROR_AND_EXIT(desc) { std::cout << desc << "\n"; return 1; }
#define REPORT_ERROR_AND_THROW(desc) { std::cout << desc << "\n"; throw std::string(desc); }
#define NULL_ERROR_EXIT(test, desc) { if (!test) REPORT_ERROR_AND_EXIT(desc); }
#define NULL_ERROR_THROW(test, desc) { if (!test) REPORT_ERROR_AND_THROW(desc); }

#define CATCH_GL_ERROR(error) { if (error) { std::cout << CGLErrorString(err) << std::endl; throw std::string(CGLErrorString(err)); } }



#endif
