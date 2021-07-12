//
// Created by Anton on 17.06.2021.
//
#pragma once

#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H
#include "iostream"
#include "../OpenGL/include/glm/glm.hpp"

class shader
{
public:
    unsigned int id;
    shader(unsigned int id);
    ~shader();

    void use();
    void uniformMatrix(std::string name, glm::mat4 matrix);
};

extern shader *load_shader(const std::string& vertexFile, const std::string& fragmentFile);


#endif //GRAPHICS_SHADER_H
