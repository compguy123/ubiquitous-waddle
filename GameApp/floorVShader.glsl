
#version 330 core
layout (location = 0) in vec4 vPosition; // the position variable has attribute position 0
  
uniform mat4 ModelView;
uniform mat4 View;
uniform mat4 Projection;
void main()
{
    gl_Position = vPosition; // see how we directly give a vec3 to vec4's constructor
   
 }