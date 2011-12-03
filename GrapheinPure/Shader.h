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

#include <OpenGL/gl3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




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
    int uniformLocation(const string &name);
    int attributeLocation(const char *name);
    
    bool setUniform(const std::string &uniformName, const glm::mat4 &matrix);
};

#endif
