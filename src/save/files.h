//
// Created by Anton on 24.06.2021.
//

#ifndef GRAPHICS_FILES_H
#define GRAPHICS_FILES_H

#include <string>

#include <string>

extern bool write_binary_file(std::string filename, const char* data, size_t size);
extern unsigned int append_binary_file(std::string filename, const char* data, size_t size);
extern bool read_binary_file(std::string filename, char* data, size_t size);
extern bool read_binary_file(std::string filename, char* data, size_t offset, size_t size);

extern unsigned int calcRLE(const char* src, unsigned int length);
extern unsigned int compressRLE(const char* src, unsigned int length, char* dst);
extern unsigned int decompressRLE(const char* src, unsigned int length, char* dst, unsigned int targetLength);

#endif //GRAPHICS_FILES_H
