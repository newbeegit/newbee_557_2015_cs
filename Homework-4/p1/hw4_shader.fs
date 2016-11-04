#version 410 core                                                 
                                                                  
in vec4 pass_Color; 
in vec2 pass_texcoord;                                              
out vec4 color; 
uniform sampler2D fig;                                                  
void main(void)                                                   
{                                                                 
		color = texture(fig, pass_texcoord); 
} 