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
#include <cmath>

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

    inline mat4 transpose(mat4 &mat)
    {   
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < i; j++)
                std::swap(mat[i][j], mat[j][i]);
        
        return mat;
    }

    inline mat4 transpose(const mat4 &mat)
    {   
        mat4 M = mat;
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < i; j++)
                std::swap(M[i][j], M[j][i]);
        
        return M;
    }

    
    inline mat4 operator*(const mat4 &A, const mat4 &B)
    {
        mat4 C;
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                C[i][j] = 0;
                
                for (int p = 0; p < 4; p++)
                {
                    C[i][j] += A[i][p] * B[p][j];
                }
            }
        
        return C;
    }

    
    inline mat4 identity()
    {
        return ((vec4){ 1, 0, 0, 0 },
                (vec4){ 0, 1, 0, 0 },
                (vec4){ 0, 0, 1, 0 },
                (vec4){ 0, 0, 0, 1 });
    }
    
    inline mat4 translate(const vec3 &B)
    {
        mat4 tr = identity();
        
        tr[0][3] = B[0];
        tr[1][3] = B[1];
        tr[2][3] = B[2];
        tr[3][3] = B[3]; // should be 1.
        
                    
        return tr;
    }
    
    inline mat4 scale(const vec3 &B)
    {
        mat4 s = identity();
        
        for (int i = 0; i < 3; i++)
            s[i][i] = B[i];
        
        return s;
    }
    
    inline mat4 rotX(float t)
    {
        mat4 r = identity();
        
        r[1][1] = cos(t);
        r[1][2] = -sin(t);
        r[2][1] = sin(t);
        r[2][3] = cos(t);
        
        return r;
    }
    
    inline mat4 rotY(float t)
    {
        mat4 r = identity();
        
        r[2][2] = cos(t);
        r[2][0] = -sin(t);
        r[0][2] = sin(t);
        r[0][0] = cos(t);
        
        return r;
    }
    
    inline mat4 rotZ(float t)
    {
        mat4 r = identity();
        
        r[0][0] = cos(t);
        r[0][1] = -sin(t);
        r[1][0] = sin(t);
        r[1][1] = cos(t);
        
        return r;
    }
    
    
    inline mat4 rotate(const vec3 &B)
    {
        mat4 r = identity();
        
        return r * rotX(B[0]) * rotY(B[1]) * rotZ(B[2]);
    }
    
    // does not work yet
    inline mat4 ortho(float left, float right, 
                 float bottom, float top,
                 float near, float far)
    {
        return scale((vec3){2/(right - left), 2/(top-bottom), -2/(far-near)}) 
            * translate((vec3){-(left+right)/2, -(top+bottom)/2, -(far+near)/2});
    }
    
    
    
}

inline std::ostream &operator<<(std::ostream &o, const iso::mat4 &m)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            o << "\t" << (m[i][j]);
        o << std::endl;
    }
    
    return o;
}


#endif
