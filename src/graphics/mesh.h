//
// Created by Anton on 24.06.2021.
//

#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H


#include <cstdlib>

class Mesh
{
    unsigned int vao;
    unsigned int vbo;
    size_t vertices;
    size_t vertexSize;
public:
    Mesh(const float* buffer, size_t vertices, const int* attrs);
    ~Mesh();

    void reload(const float* buffer, size_t vertices);
    void draw(unsigned int primitive);
};


#endif //GRAPHICS_MESH_H
