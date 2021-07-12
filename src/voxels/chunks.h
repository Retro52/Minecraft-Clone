//
// Created by Anton on 24.06.2021.
//

#ifndef GRAPHICS_CHUNKS_H
#define GRAPHICS_CHUNKS_H

#include <cstdlib>
#include "../OpenGL/include/glm/glm.hpp"
#include "../graphics/mesh.h"
#include "../save/WorldFiles.h"
#include "../graphics/VoxelRenderer.h"

class Chunk;
class voxel;

class Chunks
{
public:
    Chunk** chunks;
    Chunk** chunksSecond;

    Mesh** meshes;
    Mesh** meshesSecond;

    size_t volume;
    unsigned int w,h,d;
    int ox,oy,oz;


    Chunks(int w, int h, int d, int ox, int oy, int oz);
    ~Chunks();

    Chunk* getChunk(int x, int y, int z);
    Chunk* getChunkByVoxel(int x, int y, int z);

    voxel* get(int x, int y, int z);
    void set(int x, int y, int z, int id);
    unsigned char getLight(int x, int y, int z, int channel);

    voxel* rayCast(const glm::vec3& start, const glm::vec3& dir, float maxLength, glm::vec3& end, glm::vec3& norm, glm::vec3& iend);

    void setCenter(int x, int y, int z);
    void translate(int x, int y, int z);

    bool loadVisible(WorldFiles *worldFiles);
    bool _buildMeshes(VoxelRenderer *renderer);

};


#endif //GRAPHICS_CHUNKS_H
