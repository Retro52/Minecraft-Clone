//
// Created by Anton on 23.06.2021.
//

#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

#include <iostream>
#include <string>

class Texture {
public:
    unsigned int id;
    int width;
    int height;
    Texture(unsigned int id, int width, int height);
    Texture(unsigned char* data, int width, int height);
    ~Texture();

    void bind();
    void reload(unsigned char* data);
};

extern Texture* load_texture(std::string filename);

#endif //GRAPHICS_TEXTURE_H
