#ifndef Shader_H
#define Shader_H

#include <iostream>
#include <fstream>
#include <iterator>
#include <sys/stat.h>
#include <vector>
#include <math.h>
#include <sstream>
#include <array>

#include <OpenGL/OpenGL.h>

//#include <OpenGL/gl3.h>
//#define __gl_h_
#include <OpenGL/gl3.h>
//#include <OpenGL/glext.h>


#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include <boost/foreach.hpp>

#include "Context.h"


using namespace std;

class Shader {
private:
    GLuint program;
    vector<GLuint> shaders;
    
public:
    Shader();
    ~Shader();
    
    bool compile(const std::string &file, GLenum shaderType);
    bool link();
    bool validate();
    void use();
    void unuse();
    
    int uniformLocation(const char *name);
    int attributeLocation(const char *name);
    
    static glm::mat4 viewportTranslation;
    static glm::mat4 projectionMatrix;
};

#endif
