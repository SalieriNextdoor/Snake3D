/*
 * @file font/shader.fs
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Font fragment shader.
 */
#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture1;

void main()
{
  FragColor = texture(texture1, texCoord);
  if (FragColor.rgb == vec3(0,0,0)) discard;
};

