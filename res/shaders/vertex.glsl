#version 460
layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec3 vertex_col;
out vec3 color;
void main(){
	color = vertex_col;
	gl_Position = vec4(vertex_pos, 1.0);
}