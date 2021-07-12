//
// Created by Anton on 24.06.2021.
//

#ifndef GRAPHICS_CHUNK_H
#define GRAPHICS_CHUNK_H

#define CHUNK_W 16
#define CHUNK_H 128
#define CHUNK_D 16
#define CHUNK_VOL (CHUNK_W * CHUNK_H * CHUNK_D)

class voxel;
class Lightmap;

class Chunk {
public:
    int x,y,z;
    voxel* voxels;
    Lightmap* lightmap;
    bool modified = true;
    Chunk(int x, int y, int z);
    ~Chunk();

    bool isEmpty();
};


#endif //GRAPHICS_CHUNK_H
