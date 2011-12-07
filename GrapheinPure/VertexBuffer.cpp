//
//  Buffer.cpp
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-12-01.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>

//#include "VertexBuffer.h"


template<class Layout>
VertexBuffer<Layout>::VertexBuffer()
{
    glGenBuffers(1, &array_buffer);
    glGenVertexArrays(1, &vertex_buffer);
 
}
/*
template<class Layout>
bool VertexBuffer<Layout>::enableLocation(int location, int start_index, int skip)
{
    glBindVertexArray(vertex_buffer);
    REPORTGLERROR("bind vao");
    
    glEnableVertexAttribArray(location);
    REPORTGLERROR("enable array location");

//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, position));  
    
//    std::cout << "stride: " << skip*sizeof(glm::vec4) << std::endl;
//    std::cout << "start: " << start_index * sizeof(glm::vec4) << std::endl;
    glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, skip*sizeof(iso::vec4), (GLvoid*)(start_index * sizeof(iso::vec4)));
    REPORTGLERROR("tell it vertex data");
    
    return true;
}

template<class Layout>
bool VertexBuffer<Layout>::disableLocation(int location)
{
    glBindVertexArray(vertex_buffer);
    REPORTGLERROR("bind vao");
    
    glDisableVertexAttribArray(location);
    REPORTGLERROR("disable array location");

    return true;
}*/

template<class Layout>
bool VertexBuffer<Layout>::drawTriangles(int index, int count)
{
    glBindVertexArray(vertex_buffer);
    REPORTGLERROR("select vao");
    
    glDrawArrays(GL_TRIANGLES, index, count);
    REPORTGLERROR("draw triangles");
    
    return true;
    
}

template<class Layout>
VertexBuffer<Layout> &VertexBuffer<Layout>::operator <<(const iso::vec4 &data)
{
    this->data.push_back(data);
    
    return *this;
}
template<class Layout>
VertexBuffer<Layout> &commit(VertexBuffer<Layout> &buf)
{
    glBindBuffer(GL_ARRAY_BUFFER, buf.array_buffer);
    REPORTGLERROR("bound array buffer");

    glBufferData(GL_ARRAY_BUFFER, sizeof(iso::vec4)*buf.data.size(), (GLvoid*)buf.data.data(), GL_STATIC_DRAW);
    REPORTGLERROR("Buffer array data");
    
    glBindVertexArray(buf.vertex_buffer);
    if (buf.layout.position())
    {
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 
                              buf.layout.position_skip(buf.data.size())*sizeof(iso::vec4), 
                              (GLvoid*)(buf.layout.position_start(buf.data.size()) * sizeof(iso::vec4)));
    } 
    if (buf.layout.colour())
    {
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 
                              buf.layout.colour_skip(buf.data.size())*sizeof(iso::vec4), 
                              (GLvoid*)(buf.layout.colour_start(buf.data.size()) * sizeof(iso::vec4)));
    } 

    return buf;
}

template<class Layout>
VertexBuffer<Layout> &operator<<(VertexBuffer<Layout>&buf, VertexBuffer<Layout> &(*f)(VertexBuffer<Layout> &))
{
    return f(buf);
}
