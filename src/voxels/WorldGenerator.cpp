//
// Created by Anton on 25.06.2021.
//

#include "WorldGenerator.h"
#include "../OpenGL/include/glm/glm.hpp"
#include "../OpenGL/include/glm/gtc/noise.hpp"
#include "voxel.h"
#include "chunk.h"
#include "iostream"


void WorldGenerator::generate(voxel* voxels, int cx, int cy, int cz)
{
    int water = 7;
    for (int z = 0; z < CHUNK_D; z++)
    {
        int h = rand() % 2 + 6;
        for (int x = 0; x < CHUNK_W; x++)
        {
            int real_x = x + cx * CHUNK_W;
            int real_z = z + cz * CHUNK_D;
            float height = glm::perlin(glm::vec3(real_x*0.0125f,real_z*0.0125f, 0.0f));
            height += glm::perlin(glm::vec3(real_x*0.055f,real_z*0.055f, 0.21f))*0.5f;
            height *= 0.175f;
            height += 0.15f;
            for (int y = 0; y < CHUNK_H; y++)
            {
                int real_y = y + cy * CHUNK_H;
                float noise = height;
                int id = noise / std::fmax(0.01f, real_y*0.1f + 0.1f) > 0.1f;

                if (real_y < 3)
                    id = 1;

                if (real_y > 2 && real_y <= h && id != 0)
                    id = 1;

                else if (h < real_y && real_y < 25 + 3 && id != 0)
                    id = 2;

                if (real_y == water && id == 0)
                    id = 7;
                //
                
//                else if (id == 0 && real_y == 14 && height <= 0.01f)
//                    id = 3;



                voxels[(y * CHUNK_D + z) * CHUNK_W + x].id = id;
            }
        }
    }
}
