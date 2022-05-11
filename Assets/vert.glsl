#version 330
 
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 projection;

out vec3 pass_Color;

void main()
{
	pass_Color = color;
    gl_Position = projection * vec4(position, 1);
}
