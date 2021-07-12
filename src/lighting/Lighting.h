//
// Created by Anton on 25.06.2021.
//

#ifndef GRAPHICS_LIGHTING_H
#define GRAPHICS_LIGHTING_H

class Chunks;
class LightSolver;

class Lighting
{
    static Chunks* chunks;
    static LightSolver* solverR;
    static LightSolver* solverG;
    static LightSolver* solverB;
    static LightSolver* solverS;
public:
    static int initialize(Chunks* chunks);
    static void finalize();

    static void clear();
    static void onChunkLoaded(int cx, int cy, int cz);
    static void onBlockSet(int x, int y, int z, int id);
};


#endif //GRAPHICS_LIGHTING_H
