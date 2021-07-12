//
// Created by Anton on 25.06.2021.
//

#ifndef GRAPHICS_LIGHTSOLVER_H
#define GRAPHICS_LIGHTSOLVER_H


#include <queue>

class Chunks;

struct lightentry {
    int x;
    int y;
    int z;
    unsigned char light;
};

class LightSolver {
    std::queue<lightentry> addqueue;
    std::queue<lightentry> remqueue;
    Chunks* chunks;
    int channel;
public:
    LightSolver(Chunks* chunks, int channel);

    void add(int x, int y, int z);
    void add(int x, int y, int z, int emission);
    void remove(int x, int y, int z);
    void solve();
};


#endif //GRAPHICS_LIGHTSOLVER_H
