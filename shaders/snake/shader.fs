#version 330 core

out vec4 FragColor;

in vec4 sharedColor;

void main()
{
  FragColor = sharedColor;
};

