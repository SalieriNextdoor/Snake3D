/*
 * @file font/shader.vs
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Font vertex shader.
 */
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 model;

uniform vec2 texPos;

void main()
{
  gl_Position = model * vec4(aPos, 1.0f);
  texCoord = aTexCoord + texPos;
};

