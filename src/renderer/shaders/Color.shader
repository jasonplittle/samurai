#shader vertex
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_MVP;

out vec2 v_texCoord;

void main()
{
    gl_Position = u_MVP * a_position;
    v_texCoord = a_texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color1;
uniform vec4 u_Color2;
uniform vec4 u_Color3;

in vec2 v_texCoord;

void main()
{
    vec4 gradient = mix(u_Color1, u_Color2, v_texCoord.y);
    color = mix(gradient, u_Color3, 0.15);
};
