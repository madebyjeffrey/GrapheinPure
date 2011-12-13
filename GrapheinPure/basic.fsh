#version 150

layout(location = 0) out vec4 FragColor;

in vec4 colour;
in vec4 pos;

// pour le ES, utilisez MOD/FLOOR

void main()
{
    vec4 white = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    
    int X = int(pos.x / 10.0);

    FragColor =  ((X & 1) == 0) ? colour : (white - colour);

}
