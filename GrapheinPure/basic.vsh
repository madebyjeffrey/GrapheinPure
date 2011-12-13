#version 150

layout(location = 0) in vec4 Vposition;
layout(location = 1) in vec4 Vcolour;

uniform mat4    ProjectionMatrix;
out vec4 colour;
out vec4 pos;
    
void main()
{
    colour = Vcolour;
    pos = Vposition;
    gl_Position = ProjectionMatrix * Vposition; // ModelViewMatrix * Vertex;
}

