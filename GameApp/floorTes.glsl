#version 400

// tessellation evaluation shader

// this is invoked from the TCS, once for each generated vertex
// like a vertex shader, it needs to output vertex position in gl_Position
// as input, it receives:
//  - gl_in[GL_PATCH_VERTICES] as the TCS
//  - vec3 gl_TessCoord, which is the barycentric coordinate of the vertex
//  - any arrays ouput from the TCS (must be declared)
// it can also output per-fragment values to the fragment shader

// this line is required: layout (...) in;
// the first value "triangles" is required (other options: quads, isolines)
//   and is used to choose how the patch will be tessellated
// the other two are the default (spacing between vertices, winding)
layout (quads, equal_spacing, ccw) in;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform int subdivision;
uniform mat4 View;


vec3 N, L, E;

out vec2 TexCoord;
out vec3 col;


uniform vec3 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform float Shininess;


uniform struct AmbientLight {
    vec3 color;
} ambientLight;

uniform struct DirectionalLight {
    vec3 direction;
    vec3 color;
} directionalLight;

uniform struct PointLight {
    vec3 position;
    vec3 color;
} pointLight;

uniform struct SpotLight {
    vec3 position;
    vec3 direction;
    float cosCutoff;
    vec3 color;
} spotLight;






void main() {

float ratio = 1.0f/subdivision;
float t = gl_TessCoord.s;
vec4 p1 = gl_in[0].gl_Position*(1-t) + gl_in[3].gl_Position*t;
vec4 p2 = gl_in[1].gl_Position*(1-t) + gl_in[2].gl_Position*t;
t = gl_TessCoord.t;
vec4 pos = p1*(1-t) + p2*t;

//for normals 
vec3 vPos = (ModelView*pos).xyz;
//L = normalize( LightPosition.xyz -vPos );
E = normalize( -vPos );

//floor points up 
N= vec3(0,1,0);



   vec3 outCol=  AmbientProduct* ambientLight.color;
           

    vec3 ld = normalize(directionalLight.direction);
    ld *= -1;


    //directional light
     //diffuse product 
    outCol+=clamp(DiffuseProduct * directionalLight.color * dot(N,ld),0.0f,1.0f);
     //specular
    vec3 reflection = (2 *dot(N, ld) *N) - ld;
	reflection = normalize(reflection);
	vec3 eye = (-vPos);
    outCol+= clamp( SpecularProduct * directionalLight.color * pow(dot(reflection, eye), Shininess), 0.0f, 1.0f);
   


//for texture 
TexCoord = gl_TessCoord.xy;
col= outCol;

gl_Position = Projection*View*ModelView*pos;
  
}