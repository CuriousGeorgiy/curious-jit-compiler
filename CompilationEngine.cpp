#include "CompilationEngine.hpp"

#include <cstdio>
#include <cstring>

#include <algorithm>

#include <sys/mman.h>

Imm CompilationEngine::scanVal = 0;
Imm CompilationEngine::ebx = 0, CompilationEngine::esp = 0, CompilationEngine::ebp = 0, CompilationEngine::esi = 0, CompilationEngine::edi = 0;

CompilationEngine::CompilationEngine(const char *const bcFileName)
: bcInstrs(), mc()
{
    std::FILE *bcFileHandle = fopen(bcFileName, "rb");
    std::fseek(bcFileHandle, sizeof(short) + sizeof(char), SEEK_SET);

    std::size_t bcSz = 0;
    fread(&bcSz, sizeof(bcSz), 1, bcFileHandle);

    auto bc = static_cast<char *>(std::calloc(bcSz, sizeof(char)));

    std::fread(bc, sizeof(*bc), bcSz, bcFileHandle);
    std::fclose(bcFileHandle);

    parse(bc, bcSz);
    std::free(bc);

    translate();
}

void CompilationEngine::parse(const char *const bc, std::size_t sz)
{
    const char *reader = bc;

    while (reader != bc + sz) {
        auto opcode = static_cast<BytecodeInstruction::Opcode>(*reader);
        Imm instrAddr = std::distance(bc, reader);
        reader += sizeof(char);

        ReadWriteMode readWriteMode{};
        VirtualMachine::Reg reg = VirtualMachine::Reg::Undefined;
        Imm imm = 0;
        Imm jmpAddr = 0;
        switch (opcode) {
            case BytecodeInstruction::Opcode::hlt:
            case BytecodeInstruction::Opcode::dump:
            case BytecodeInstruction::Opcode::in:
            case BytecodeInstruction::Opcode::out:
            case BytecodeInstruction::Opcode::ret:
            case BytecodeInstruction::Opcode::neg:
            case BytecodeInstruction::Opcode::add:
            case BytecodeInstruction::Opcode::sub:
            case BytecodeInstruction::Opcode::mul:
            case BytecodeInstruction::Opcode::div:
            case BytecodeInstruction::Opcode::pow:
            case BytecodeInstruction::Opcode::sqrt:
                bcInstrs.emplace_back(opcode, instrAddr);

                break;

            case BytecodeInstruction::Opcode::push:
            case BytecodeInstruction::Opcode::pop:
                readWriteMode.mode = static_cast<char>(*reader);
                reader += sizeof(char);

                if (readWriteMode.reg & readWriteMode.imm) {
                    reg = static_cast<VirtualMachine::Reg>(*reader);
                    reader += sizeof(char);

                    imm = *reinterpret_cast<const Imm *>(reader);
                    reader += sizeof(Imm);
                } else if (readWriteMode.reg & !readWriteMode.imm) {
                    reg = static_cast<VirtualMachine::Reg>(*reader);
                    reader += sizeof(char);
                } else if (readWriteMode.imm & !readWriteMode.reg) {
                    imm = *reinterpret_cast<const Imm *>(reader);
                    reader += sizeof(Imm);
                }

                bcInstrs.emplace_back(opcode, instrAddr, 0, readWriteMode, reg, imm);

                break;

            case BytecodeInstruction::Opcode::jmp:
            case BytecodeInstruction::Opcode::ja:
            case BytecodeInstruction::Opcode::jae:
            case BytecodeInstruction::Opcode::jb:
            case BytecodeInstruction::Opcode::jbe:
            case BytecodeInstruction::Opcode::je:
            case BytecodeInstruction::Opcode::jne:
            case BytecodeInstruction::Opcode::call:
                jmpAddr = *reinterpret_cast<const Imm *>(reader);
                reader += sizeof(Imm);

                bcInstrs.emplace_back(opcode, instrAddr, jmpAddr);

                break;
        }
    }
}

void CompilationEngine::translate()
{
#define TRANSLATE_PM_OPC(opc) BytecodeInstruction::translateOpcToBack(&mc, (opc))
#define TRANSLATE_ADDR(addr) BytecodeInstruction::translateImmToBack(&mc, (addr))
    TRANSLATE_PM_OPC(PhysicalMachine::Opcode::MovRamEbx);
    TRANSLATE_ADDR(reinterpret_cast<Imm>(&ebx));
    TRANSLATE_PM_OPC(PhysicalMachine::Opcode::MovRamEsp);
    TRANSLATE_ADDR(reinterpret_cast<Imm>(&esp));
    TRANSLATE_PM_OPC(PhysicalMachine::Opcode::MovRamEbp);
    TRANSLATE_ADDR(reinterpret_cast<Imm>(&ebp));
    TRANSLATE_PM_OPC(PhysicalMachine::Opcode::MovRamEsi);
    TRANSLATE_ADDR(reinterpret_cast<Imm>(&esi));
    TRANSLATE_PM_OPC(PhysicalMachine::Opcode::MovRamEdi);
    TRANSLATE_ADDR(reinterpret_cast<Imm>(&edi));
#undef TRANSLATE_ADDR
#undef TRANSLATE_PM_OPC

    for (auto &bcInstr: bcInstrs) bcInstr.translateToBack(&mc);

    for (auto &bcInstr: bcInstrs) {
        if (BytecodeInstruction::isJmp(bcInstr)) {
            auto targetBcInstr = std::find_if(bcInstrs.cbegin(), bcInstrs.cend(), [&bcInstr](BytecodeInstruction otherBcInstr)
            { return otherBcInstr.bcInstrAddr == bcInstr.bcJmpAddr; });

            BytecodeInstruction::translateImmToRelAddr(&mc, bcInstr.mcRelJmpInstrOperandAddrToPatch,
                                                       static_cast<Imm>(targetBcInstr->mcRelInstrAddr) -
                                                       (static_cast<Imm>(bcInstr.mcRelInstrAddr + bcInstr.pmJmpInstrSz())));
        }
    }
}

void CompilationEngine::run() const
{
    void *exec = mmap(nullptr, mc.size(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    std::memcpy(exec, &mc[0], mc.size());
    mprotect(exec, mc.size(), PROT_READ | PROT_EXEC);
    reinterpret_cast<void (*)()>(exec)();
}
