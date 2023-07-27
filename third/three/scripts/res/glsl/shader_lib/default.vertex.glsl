layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 frag_normal;
out vec3 frag_position;

uniform mat4 model_matrix;
uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform mat4 normal_matrix;

void main()
{
  
  gl_Position = projection_matrix * model_view_matrix * vec4(position, 1.0);
  frag_position = (model_matrix * vec4(position, 1.0)).xyz;
  frag_normal = normal;
}