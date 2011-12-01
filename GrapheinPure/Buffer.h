//
//  Buffer.h
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-12-01.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GrapheinPure_Buffer_h
#define GrapheinPure_Buffer_h

#include <vector>

#include <OpenGL/gl3.h>

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

class VertexBuffer
{
    std::vector<glm::vec4> data;
    GLuint array_buffer;
    GLuint vertex_buffer;
    
public:
    VertexBuffer();

    bool buffer(int count, const glm::vec4 *glm);
    
    bool enableLocation(int location, int start_index, int skip);
    bool disableLocation(int location);
    bool drawTriangles(int index, int count);
};

#endif
