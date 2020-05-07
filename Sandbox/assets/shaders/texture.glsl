#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_textCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

out vec2 v_textCoord;

void main() {
    v_textCoord = a_textCoord;
    gl_Position = u_viewProjection * u_transform * vec4(a_position, 1);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_color;

in vec2 v_textCoord;

uniform sampler2D u_texture;

void main() {
    o_color = texture(u_texture, v_textCoord);
}
