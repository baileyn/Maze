#version 330
 
in vec3 pass_Color;
out vec4 outputColor;
 
void main()
{
    outputColor = vec4(pass_Color, 1);
}
