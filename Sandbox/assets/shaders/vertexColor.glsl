#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

void main() {
    gl_Position = u_viewProjection * u_transform * vec4(a_position, 1);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_color;

uniform vec4 u_color;

void main() {
    o_color = u_color;
}
