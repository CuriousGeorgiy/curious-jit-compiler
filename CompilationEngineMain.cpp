#include <cstdio>
#include <cstdlib>

#include "CompilationEngine.hpp"

int main(int argc, const char *argv[])
{
    --argc;

    if (argc == 0 || argc > 1) {
        printf("usage: curious-jit <bytecode file name>\n");

        return EXIT_SUCCESS;
    }

    const char *const inputFileName = argv[1];

    CompilationEngine ce(inputFileName);
    ce.run();

    printf("Successfully executed input file\n");

    return EXIT_SUCCESS;
}
