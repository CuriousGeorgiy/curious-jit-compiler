#ifndef TEXT_HPP
#define TEXT_HPP

#include <cstddef>

class Text {
public:
    struct Line {
        char *str;
        std::size_t len;
    };

    Line *lines;
    std::size_t nLines;

    explicit Text(const char *inputFileName);

    Text(const Text &) = delete;
    Text(Text &&) = delete;

    Text &operator=(const Text &) = delete;
    Text &operator=(Text &&) = delete;

    ~Text();
private:
    char *buf;
    const char *inputFileName;

    void readTextFileToBuf();
    void countLinesInBuf();
    void splitBufIntoLines();
};

#endif /* TEXT_HPP */
