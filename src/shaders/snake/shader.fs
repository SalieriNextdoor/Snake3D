/*
 * @file snake/shader.fs
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Model fragment shader.
 */
#version 330 core

out vec4 FragColor;

in vec4 sharedColor;

void main()
{
  FragColor = sharedColor;
};

