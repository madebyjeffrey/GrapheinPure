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

#include "glError.h"

#include "iso.h"

class PCPacked
{
public:
    bool position() 
    {
        return true;
    }
    
    bool colour()
    {
        return true;
    }
    
    size_t position_index(size_t elements)
    {
        return 0;
    }
    size_t colour_index(size_t elements)
    {
        return 1;
    }
    size_t position_skip(size_t elements)
    {
        return 2;
    }
    size_t colour_skip(size_t elements)
    {
        return 2;
    }
};

template<class Layout=PCPacked>
class VertexBuffer;

template<class Layout>
VertexBuffer<Layout> &commit(VertexBuffer<Layout> &);

template<class Layout>
VertexBuffer<Layout> &operator<<(VertexBuffer<Layout>&, VertexBuffer<Layout> &(*)(VertexBuffer<Layout> &));

template<class Layout>
class VertexBuffer
{
    friend VertexBuffer<Layout> &commit<>(VertexBuffer<Layout> &);
    
    std::vector<iso::vec4> data;
    GLuint array_buffer;
    GLuint vertex_buffer;
    Layout layout;

//    bool enableLocation(int location, int start_index, int skip);
//    bool disableLocation(int location);

public:
    VertexBuffer()
    {
        glGenBuffers(1, &array_buffer);
        glGenVertexArrays(1, &vertex_buffer);
        
    }
    
    bool drawTriangles(int index, int count)
    {
        glBindVertexArray(vertex_buffer);
        REPORTGLERROR("select vao");
        
        glDrawArrays(GL_TRIANGLES, index, count);
        REPORTGLERROR("draw triangles");
        
        return true;
        
    }

    VertexBuffer &operator <<(iso::vec4 const &data)   // buffer data
    {
        this->data.push_back(data);
        
        return *this;
    }
    
    
};

template <typename Layout>
VertexBuffer<Layout> &commit(VertexBuffer<Layout> &buf)
{
    glBindBuffer(GL_ARRAY_BUFFER, buf.array_buffer);
    REPORTGLERROR("bound array buffer");
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(iso::vec4)*buf.data.size(), (GLvoid*)buf.data.data(), GL_STATIC_DRAW);
    REPORTGLERROR("Buffer array data");

    glBindVertexArray(buf.vertex_buffer);

    if (buf.layout.position())
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 
                              (GLsizei)buf.layout.position_skip(buf.data.size())*sizeof(iso::vec4), 
                              (GLvoid*)(buf.layout.position_index(buf.data.size()) * sizeof(iso::vec4)));
    } 
    if (buf.layout.colour())
    {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 
                              (GLsizei)buf.layout.colour_skip(buf.data.size())*sizeof(iso::vec4), 
                              (GLvoid*)(buf.layout.colour_index(buf.data.size()) * sizeof(iso::vec4)));
    } 
    
    return buf;
}// upload it

template<class Layout>
VertexBuffer<Layout> &operator<<(VertexBuffer<Layout>&buf, VertexBuffer<Layout> &(*f)(VertexBuffer<Layout> &))
{
    return f(buf);
}


#endif