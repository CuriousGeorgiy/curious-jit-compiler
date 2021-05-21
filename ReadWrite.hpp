#ifndef READWRITE_HPP
#define READWRITE_HPP

union ReadWriteMode {
    struct {
        int imm: 1;
        int reg: 1;
        int ram: 1;
    };
    char mode;
};

typedef int Imm;

#endif /* READWRITE_HPP */
