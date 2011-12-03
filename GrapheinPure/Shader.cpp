#include "Shader.h"

#include "Context.h"

using namespace std;


Shader::Shader() : program(0), shaders(vector<GLuint>()) 
{
}

Shader::~Shader() 
{
    if (program)
        glDeleteProgram(program);
    // run through shaders to delete them
}

bool Shader::compile(const string &file, GLenum shaderType)
{
	ifstream shaderFile;
    
	shaderFile.open(file.c_str(), ios::binary);
	stringstream in;
	in << shaderFile.rdbuf();
	string source(in.str());
	
    const char *str = source.c_str();
    
    if (str == NULL)
    {
        cout << "Failed to read shader file " << file << endl;
    }

    GLuint shader = glCreateShader(shaderType);
    REPORTGLERROR("create shader");
    
    glShaderSource(shader, 1, &str, NULL);
    REPORTGLERROR("load source");
    
    glCompileShader(shader);
    REPORTGLERROR("compile shader");

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    REPORTGLERROR("check compile status");
		
    if (status == GL_FALSE) 
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        
        const char *strShaderType = NULL;
        switch(shaderType)
        {
            case GL_VERTEX_SHADER: strShaderType = "Vertex"; break;
//            case GL_GEOMETRY_SHADER: strShaderType = "Geometry"; break;
            case GL_FRAGMENT_SHADER: strShaderType = "Fragment"; break;
        }
        
        cerr << strShaderType << " shader " << file << "failed to compiled." << endl;
        cerr << "Log:" << endl << strInfoLog << endl;
        
        delete[] strInfoLog;
        glDeleteShader(shader);
        
        return false;
    }
    
    shaders.push_back(shader);
    
	return true;
}

bool Shader::link()
{
    program = glCreateProgram();
    REPORTGLERROR("Create program");
    
    for (auto s : shaders)
    {
        glAttachShader(program, s);
        REPORTGLERROR("attach shader");
    }
    
    if (!program) {
        std::cerr << "Program handle invalid." << std::endl;
        return false;
    }
	
	glLinkProgram(program);
    REPORTGLERROR("link program");
	
	GLint status;
	
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		
		std::cerr << "Linker failure: " << strInfoLog << std::endl;
		
		delete[] strInfoLog;
		
		return false;
	}
    REPORTGLERROR("end of link function");
	return true;
}

bool Shader::validate()
{
    GLint logLength;
    
    glValidateProgram(program);
    REPORTGLERROR("Validate program");
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    REPORTGLERROR("check error log");
    if (logLength > 0)
    {
        GLchar *log = new GLchar[logLength]; 
        glGetProgramInfoLog(program, logLength, NULL, log);
        REPORTGLERROR("get error log");
        cout << "Program validation produced errors:" << endl << log << endl;;
        free(log);
        return false;
    }
    
    GLint status;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    REPORTGLERROR("get status of validation");
    if (0 == status)
    {
        cout << "Failed to link shader program." << endl;
        return false;
    }
    return true;
} 


void Shader::use()
{
    glUseProgram(program); 
    REPORTGLERROR("use program");
}

void Shader::unuse()
{
    glUseProgram(0); 
    REPORTGLERROR("unuse program");
}

int Shader::uniformLocation(const char *name)
{    
    return glGetUniformLocation(this->program, name);
}

int Shader::uniformLocation(const string &name)
{
    return uniformLocation(name.c_str());
}

int Shader::attributeLocation(const char *name)
{
    return glGetAttribLocation(this->program, name);
}


bool Shader::setUniform(const std::string &uniformName, const glm::mat4 &matrix)
{
    int uniform = uniformLocation(uniformName);
    REPORTGLERROR("Check uniform location");
    if (uniform == -1) return false;
    
    GLenum type;
    
    glGetActiveUniform(program, uniform, 0, NULL, NULL, &type, NULL);
    REPORTGLERROR("Get uniform type info");
    
    if (type == GL_FLOAT_MAT4)
    {
        glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));
        REPORTGLERROR("Give uniform data");
        return true;
    }
    
    return false;
}
