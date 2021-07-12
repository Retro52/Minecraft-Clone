//
// Created by Anton on 25.06.2021.
//

#ifndef GRAPHICS_WORLDGENERATOR_H
#define GRAPHICS_WORLDGENERATOR_H


class voxel;

class WorldGenerator
{
public:
    static void generate(voxel* voxels, int x, int y, int z);
};


#endif //GRAPHICS_WORLDGENERATOR_H
