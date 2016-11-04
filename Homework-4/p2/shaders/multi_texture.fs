#version 410 core                                                 

uniform sampler2D sunset; //this is the texture
uniform sampler2D gradient; //this is the texture
uniform sampler2D person; //this is the texture

in vec2 pass_TexCoord; //this is the texture coord
in vec4 pass_Color;
out vec4 color;

uniform int texture_blend;

void main(void)                                                   
{
    // This function finds the color component for each texture coordinate. 
    vec4 fig1 =  texture(sunset, pass_TexCoord);
    
    vec4 fig2 =  texture(gradient, pass_TexCoord);
    
    vec4 fig3 =  texture(person, pass_TexCoord);
    
    
	
	color = fig1*fig2 * fig3*4;
	
}