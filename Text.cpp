#include "Text.hpp"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/stat.h>

Text::Text(const char *inputFileName)
: buf(nullptr), lines(nullptr), inputFileName(inputFileName), nLines(0)
{
    assert(inputFileName != nullptr);

    readTextFileToBuf();
    countLinesInBuf();
    splitBufIntoLines();
}

Text::~Text()
{
    std::free(lines);
    std::free(buf);
}

void Text::readTextFileToBuf()
{
    struct stat st{};
    stat(inputFileName, &st);

    buf = (char *) std::calloc(st.st_size + 2, sizeof(char));

    FILE *inputFileHandle = fopen(inputFileName, "rb");
    fread(buf + 1, sizeof(char), st.st_size, inputFileHandle);
    fclose(inputFileHandle);
}

void Text::countLinesInBuf()
{
    int preChar = EOF;

    const char *reader = buf + 1;

    while (*reader) {
        if ((*reader == '\n') && (preChar != '\n') && (preChar != EOF)) ++nLines;
        preChar = (unsigned char) *(reader++);
    }

    if ((preChar != '\n') && (preChar != EOF)) ++nLines;
}

void Text::splitBufIntoLines()
{
    lines = (Line *) std::calloc(nLines + 1, sizeof(Text::Line));

    lines[0].str = std::strtok(buf + 1, "\n");

    lines[0].str[-1] = '\0';
    lines[0].len = strlen(lines[0].str);

    for (size_t i = 1; i < nLines; ++i) {
        lines[i].str = std::strtok(nullptr, "\n");

        lines[i].str[-1] = '\0';
        lines[i].len = strlen(lines[i].str);
    }
}
