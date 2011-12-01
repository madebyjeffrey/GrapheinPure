#version 150


layout(location = 0) out vec4 FragColor;

in vec4 colour;

void main()
{
//    outputColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    FragColor = colour;
//    vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
