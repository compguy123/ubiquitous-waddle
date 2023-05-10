#version 400


// tessellation control shader

// this is invoked once for each vertex in the input patch
// the vertex has already gone through the vertex shader
// each invocation has access to all of the patch's data, in arrays

// default input is in an array gl_in[GL_PATCH_VERTICES] (from C++ code)
// it is an array of structs; one field is gl_Position from the vertex shader

// note: in the C++ code only four new lines of code are *required*
//       these are marked with the notation "TESS" in the comments

// the number of vertices in the output patch; here it is the same as input


// the color array is received from the output of the vertex shader
// (again, one array element per vertex in the patch)
// the output is sent to the tessellation evaluation shader
uniform int subdivision;
layout (vertices = 4) out;



void main() {


  if (gl_InvocationID == 0) {
  // This determines how the patch will be tessellated; see
    // https://www.khronos.org/opengl/wiki/Tessellation#Tessellating_primitives
    // done once for each patch
    gl_TessLevelInner[0] = subdivision;
    gl_TessLevelInner[1] = subdivision;

    gl_TessLevelOuter[0] = subdivision;
    gl_TessLevelOuter[1] = subdivision;
    gl_TessLevelOuter[2] = subdivision;
    gl_TessLevelOuter[3] = subdivision;
  }
  
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
  
}