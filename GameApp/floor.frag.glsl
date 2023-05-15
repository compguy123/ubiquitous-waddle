#version 150


out vec4 fColor;
uniform sampler2D texture;
in vec2 TexCoord;
in vec3 col;


void main() 
{ 
           fColor =vec4(0,0,0,1);
        
           fColor.xyz = col;


            vec4 texColor = texture2D(texture, TexCoord);
            fColor.xyz *=texColor.xyz;

}

