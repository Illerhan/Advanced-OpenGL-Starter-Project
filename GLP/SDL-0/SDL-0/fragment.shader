#version 330 core
out vec4 FragColor;
in ourColor
out vec4 color;
//uniform vec4 ourColor;
void main()
{
	color = ourColor;
	//FragColor = ourColor;
}