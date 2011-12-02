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
    template<typename T=float>
    class vec4
    {
        array<T,4> vec;
        
    public:
        vec4() : vec({0, 0, 0, 0}) {} //: x(0), y(0), z(0), w(0) {} 
        vec4(T _x, T _y, T _z, T _w) : vec({_x, _y, _z, _w}) {} //x(_x), y(_y), z(_z), w(_w) {}
        
        T &operator[](int n) {
            return vec[n];
        }
        
        const T*data()
        {
            return vec.data();
        }
    };

    template<typename T=float>
    class mat4
    {
        std::array<vec4<T>, 4> mat;
        
    public:
        mat4(vec4<T> v0, vec4<T> v1, vec4<T> v2, vec4<T> v3) 
        {
            mat[0] = v0;
            mat[1] = v1;
            mat[2] = v2;
            mat[3] = v3;
        }
        
        vec4<T> &operator[](int i)
        {
            return mat[i];
        }
                
        void transpose()     // transpose inplace
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    std::swap(mat[i][j], mat[j][i]);
                }
            }
        }
        
        const T*data()
        {
            return (T*)&mat[0];
        }
    };
    
    template<typename T=float>
    std::ostream &operator<<(std::ostream &o, mat4<T> &m)
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
