
GrapheinPure
============

GP is an experiment in first creating a rendering system that can output an
OpenGL rendered scene to an image file.

The [original code](http://lists.apple.com/archives/mac-opengl/2010/Jun/msg00080.html)
 was an Objective C++ program from the Apple Mac-OpenGL mailing list.
 
After verifying it would work, I slowly converted it away from Objective C++ 
to plain old C++, and eventually even updated it to be a modern OpenGL 3.2
application.

Afterwards, the various components are abstracted away making the source code
very nice. But the abstractions were not necessarily a good design.

My next task is to standardize how errors are reporting and make sure the
components fit together. Ultimately I want to implement a scenegraph library
for 2D rendering on this, and even extend it to other platforms.

Any thoughts are welcome with regards to design.

I intend to keep compatibility between GCC 4.6, Clang 3, and MSVC 2010. 
C++ 11 is a primary development target.

Required libraries: libpng, boost, glm.

