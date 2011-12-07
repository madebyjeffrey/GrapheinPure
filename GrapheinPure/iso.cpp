//
//  iso.cpp
//  GrapheinPure
//
//  Created by Jeffrey Drake on 11-12-05.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>


#include "iso.h"

namespace iso {

template <typename T, std::size_t Y>
T x(std::array<T,Y> v)
{
    static_assert(Y >= 1, "Array has no x value.");
    return v[0];
}

template <typename T, std::size_t Y>
T y(std::array<T,Y> v)
{
    static_assert(Y >= 2, "Array has no y value.");
    return v[1];
}

template <typename T, std::size_t Y>
T z(std::array<T,Y> v)
{
    static_assert(Y >= 3, "Array has no z value.");
    return v[2];
}

    iso::mat4x2 operator ,(const     iso::vec4 &x, const     iso::vec4 &y)
{
    mat4x2 m = { x, y };
    return m;
}

mat4x3 operator ,(const mat4x2 &x, const vec4 &y)
{
    mat4x3 m = { x[0], x[1], y };
    return m;
}
mat4x3 operator ,(const vec4 &y, const mat4x2 &x );
mat4x3 operator ,(const vec4 &y, const mat4x2 &x )
{
    mat4x3 m = { x[0], x[1], y };
    return m;
}

mat4 operator ,(const mat4x3 &x, const vec4 &y)
{
    mat4 m = {x[0], x[1], x[2], y};
    return m;
}

mat4 ortho2d(float left, float right, 
             float bottom, float top,
             float near, float far)
{
    //vec4 z {2/(right-left), 0, 0, -(right+left)/(right-left)};
    
    //        return (((z,z),z),z);
    return ((vec4){2/(right-left), 0, 0, -(right+left)/(right-left)},
            (vec4){0, 2/(top-bottom), 0, -(top+bottom)/(top-bottom)},
            (vec4){0, 0, -2/(far - near), -(far+near)/(far-near)},
            (vec4){0, 0, 0, 1}); 
}

}
