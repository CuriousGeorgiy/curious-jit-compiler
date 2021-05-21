#ifndef FILE_HPP
#define FILE_HPP

#include <cstdio>

long countFileSize(std::FILE *file);

char *readBinaryFileToBuf(std::FILE *binaryFile);

#endif /* FILE_HPP */
