//
// Created by Anton on 24.06.2021.
//

#ifndef GRAPHICS_VOXELRENDERER_H
#define GRAPHICS_VOXELRENDERER_H


#include <cstdlib>

class Mesh;
class Chunk;

class VoxelRenderer
{
    float* buffer;
    size_t capacity;
public:
    explicit VoxelRenderer(size_t capacity);
    ~VoxelRenderer();

    Mesh* render(Chunk* chunk, const Chunk** chunks);
};


#endif //GRAPHICS_VOXELRENDERER_H
