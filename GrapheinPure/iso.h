//
//  iso.h
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-12-01.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GrapheinPure_iso_h
#define GrapheinPure_iso_h

#include <array>
#include <iostream>

namespace iso 
{
    typedef std::array<float,2> vec2;
    typedef std::array<float,3> vec3;
    typedef std::array<float,4> vec4;

    template <typename T, std::size_t Y>
    T x(std::array<T,Y> v);

    template <typename T, std::size_t Y>
    T y(std::array<T,Y> v);
    
    template <typename T, std::size_t Y>
    T z(std::array<T,Y> v);
    
    typedef std::array<vec4,2> mat4x2;
    typedef std::array<vec4,3> mat4x3;
    typedef std::array<vec4,4> mat4;


    mat4x2 operator ,(const vec4 &x, const vec4 &y);
    mat4x3 operator ,(const mat4x2 &x, const vec4 &y);
    mat4 operator ,(const mat4x3 &x, const vec4 &y);
    
    mat4 ortho2d(float left, float right, 
                 float top, float bottom,
                 float far, float near);
    
    inline void transpose(mat4 &mat)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < i; j++)
                std::swap(mat[i][j], mat[j][i]);
    }
    /*
    inline mat4 operator*(const mat4 &A, const mat4 &B)
    {
        mat4 C;
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; i++)
                C[i][j] = accumulate(
    }*/
    
    template<typename T>
    std::ostream &operator<<(std::ostream &o, const mat4 &m)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                o << "\t" << (m[i][j]);
            o << std::endl;
        }
        
        return o;
    }
    
}

#endif
