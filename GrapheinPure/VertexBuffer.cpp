//
//  Buffer.cpp
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-12-01.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "VertexBuffer.h"
#include "Context.h"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &array_buffer);
    glGenVertexArrays(1, &vertex_buffer);
    
}

bool VertexBuffer::buffer(int count, const glm::vec4 *pos)
{
    for (int i = 0; i < count; i++)
    {
        data.push_back(pos[i]);
        
        std::cout << "(" << pos[i].x << ", " << pos[i].y << ", " 
             << pos[i].z << ", " << pos[i].w << ")" << std::endl;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, array_buffer);
    REPORTGLERROR("bound array buffer");
    std::cout << "size: " << sizeof(glm::vec4) << std::endl;
    
    std::cout << "size: " << data.size() << std::endl;
    
    std::cout << "size: " << sizeof(glm::vec4)*data.size() << std::endl;
    
    //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*data.size(), (GLvoid*)&data[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*data.size(), (GLvoid*)data.data(), GL_STATIC_DRAW);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(position), (GLvoid*)position, GL_STATIC_DRAW);
    REPORTGLERROR("Buffer array data");

    return true;
}

bool VertexBuffer::enableLocation(int location, int start_index, int skip)
{
    glBindVertexArray(vertex_buffer);
    REPORTGLERROR("bind vao");
    
    glEnableVertexAttribArray(location);
    REPORTGLERROR("enable array location");

//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, position));  
    
    std::cout << "stride: " << skip*sizeof(glm::vec4) << std::endl;
    std::cout << "start: " << start_index * sizeof(glm::vec4) << std::endl;
    glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, skip*sizeof(glm::vec4), (GLvoid*)(start_index * sizeof(glm::vec4)));
    REPORTGLERROR("tell it vertex data");
    
    return true;
}

bool VertexBuffer::disableLocation(int location)
{
    glBindVertexArray(vertex_buffer);
    REPORTGLERROR("bind vao");
    
    glDisableVertexAttribArray(location);
    REPORTGLERROR("disable array location");

    return true;
}

bool VertexBuffer::drawTriangles(int index, int count)
{
    glBindVertexArray(vertex_buffer);
    REPORTGLERROR("select vao");
    
    glDrawArrays(GL_TRIANGLES, index, count);
    REPORTGLERROR("draw triangles");
    
    return true;
    
}