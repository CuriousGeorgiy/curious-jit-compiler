#ifndef BYTECODE_INSTRUCTION_HPP
#define BYTECODE_INSTRUCTION_HPP

#include <cstddef>

#include <vector>

#include "PhysicalMachine.hpp"
#include "ReadWrite.hpp"
#include "VirtualMachine.hpp"

class BytecodeInstruction {
public:
    enum class Opcode {
        hlt,
        dump,
        in,
        out,
        push,
        pop,
        neg,
        add,
        sub,
        mul,
        div,
        pow,
        jmp,
        ja,
        jae,
        jb,
        jbe,
        je,
        jne,
        call,
        ret,
        sqrt
    };

    BytecodeInstruction(Opcode opc, Imm bcInstrAddr, Imm bcJmpAddr = 0, ReadWriteMode rwMode = {.mode = 0},
                        VirtualMachine::Reg reg = VirtualMachine::Reg::Undefined, Imm imm = 0);

    void translateToBack(std::vector<std::byte> *mc);
    static void translateOpcToBack(std::vector<std::byte> *mc, PhysicalMachine::Opcode pmOpc);
    static void translateImmToBack(std::vector<std::byte> *mc, Imm imm);
    static void translateImmToRelAddr(std::vector<std::byte> *mc, std::size_t relMcAddr, Imm imm);

    static bool isJmp(BytecodeInstruction bcInstr);
    [[nodiscard]] std::size_t pmJmpInstrSz() const;

    Opcode opcode;
    Imm bcInstrAddr;
    Imm bcJmpAddr;
    std::size_t mcRelInstrAddr;
    std::size_t mcRelJmpInstrOperandAddrToPatch;

private:
    void translateImmToBack(std::vector<std::byte> *mc) const;

    ReadWriteMode rwMode;
    VirtualMachine::Reg reg;
    Imm imm;
};

#endif /* BYTECODE_INSTRUCTION_HPP */
