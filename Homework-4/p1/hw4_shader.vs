#version 410 core                                                 
                                                                  
uniform mat4 projectionMatrix;                                    
uniform mat4 viewMatrix;                                          
uniform mat4 modelMatrix;                                         
in vec3 in_Pos;                                              
in vec2 in_Coord;                                                                  
in vec3 in_Color;                                                 
                                             
out vec3 pass_Color; 
out vec2 pass_texcoord; 
 
void main(void)                                                   
{                                                                 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Pos, 1.0);  
    pass_Color = in_Color;     
	pass_texcoord=in_Coord;
}                      