#include "BytecodeInstruction.hpp"

#include <cstddef>

#include "CompilationEngine.hpp"

BytecodeInstruction::BytecodeInstruction(const Opcode opc, const Imm bcInstrAddr, const Imm bcJmpAddr, const ReadWriteMode
rwMode, const VirtualMachine::Reg reg, const Imm imm)
: opcode(opc), bcInstrAddr(bcInstrAddr), bcJmpAddr(bcJmpAddr), mcRelInstrAddr(0), mcRelJmpInstrOperandAddrToPatch(0), rwMode(rwMode), reg(reg), imm(imm)
{
}

void BytecodeInstruction::translateToBack(std::vector<std::byte> *const mc)
{
    mcRelInstrAddr = mc->size();

    switch (opcode) {
#define TRANSLATE_PM_OPC(opcode) translateOpcToBack(mc, (opcode))
#define TRANSLATE_IMM() translateImmToBack(mc)
#define TRANSLATE_ADDR(addr) translateImmToBack(mc, (addr))
#define TRANSLATE_REL(rel) translateImmToBack(mc, (rel))
#define TRANSLATE_VAL(val) translateImmToBack(mc, (val))

        case BytecodeInstruction::Opcode::dump:
        case BytecodeInstruction::Opcode::neg:
        case BytecodeInstruction::Opcode::pow:
        case BytecodeInstruction::Opcode::sqrt:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::Nop);

            return;

        case BytecodeInstruction::Opcode::in:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEax);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEcx);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEdx);

            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushImm);
            TRANSLATE_ADDR(reinterpret_cast<Imm>(&CompilationEngine::scanVal));
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushImm);
            TRANSLATE_ADDR(reinterpret_cast<Imm>(CompilationEngine::scanFmt));

            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::CallRel);
            TRANSLATE_REL(reinterpret_cast<Imm>(std::scanf) - (reinterpret_cast<Imm>(&mc->back()) + sizeof(Imm)));

            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::AddEsp);
            TRANSLATE_VAL(2 * sizeof(Imm));

            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdx);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEcx);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEax);

            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushImm);
            TRANSLATE_VAL(CompilationEngine::scanVal);

            return;

        case BytecodeInstruction::Opcode::out:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdi);

            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEax);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEcx);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEdx);

            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushImm);
            TRANSLATE_ADDR(reinterpret_cast<Imm>(CompilationEngine::printFmt));

            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::CallRel);
            TRANSLATE_REL(reinterpret_cast<Imm>(std::printf) - (reinterpret_cast<Imm>(&mc->back()) + sizeof(Imm)));

            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::AddEsp);
            TRANSLATE_VAL(2 * sizeof(Imm));

            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdx);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEcx);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEax);

            return;

        case BytecodeInstruction::Opcode::hlt:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::MovEbxRam);
            TRANSLATE_ADDR(reinterpret_cast<Imm>(&CompilationEngine::ebx));
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::MovEspRam);
            TRANSLATE_ADDR(reinterpret_cast<Imm>(&CompilationEngine::esp));
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::MovEbpRam);
            TRANSLATE_ADDR(reinterpret_cast<Imm>(&CompilationEngine::ebp));
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::MovEsiRam);
            TRANSLATE_ADDR(reinterpret_cast<Imm>(&CompilationEngine::esi));
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::MovEdiRam);
            TRANSLATE_ADDR(reinterpret_cast<Imm>(&CompilationEngine::edi));
        case BytecodeInstruction::Opcode::ret:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::Ret);

            return;

        case BytecodeInstruction::Opcode::add:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::AddEsiEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEdi);

            return;

        case BytecodeInstruction::Opcode::sub:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::SubEdiEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEdi);

            return;

        case BytecodeInstruction::Opcode::mul:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEax);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::MulEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEax);

            return;

        case BytecodeInstruction::Opcode::div:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEax);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::XorEdxEdx);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::DivEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEax);

            return;

        case BytecodeInstruction::Opcode::push:
            if (rwMode.ram & rwMode.reg & rwMode.imm) {
                switch (reg) {
                    case VirtualMachine::Reg::Eax:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEaxImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Ecx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEcxImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Edx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEdxImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Ebx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEbxImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Esp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEspImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Ebp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEbpImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Esi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEsiImmRam);
                        TRANSLATE_IMM();

                        return;
                    case VirtualMachine::Reg::Edi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEdiImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Undefined:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::Nop);

                        return;
                }
            } else if (rwMode.ram & rwMode.reg & ~rwMode.imm) {
                switch (reg) {
                    case VirtualMachine::Reg::Eax:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEaxRam);

                        return;

                    case VirtualMachine::Reg::Ecx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEcxRam);

                        return;

                    case VirtualMachine::Reg::Edx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEdxRam);

                        return;

                    case VirtualMachine::Reg::Ebx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEbxRam);

                        return;

                    case VirtualMachine::Reg::Esp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEspRam);

                        return;

                    case VirtualMachine::Reg::Ebp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEbpRam);

                        return;

                    case VirtualMachine::Reg::Esi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEsiRam);

                        return;
                    case VirtualMachine::Reg::Edi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEdiRam);

                        return;

                    case VirtualMachine::Reg::Undefined:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::Nop);

                        return;
                }
            } else if (~rwMode.ram & rwMode.reg & ~rwMode.imm) {
                switch (reg) {
                    case VirtualMachine::Reg::Eax:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEax);

                        return;

                    case VirtualMachine::Reg::Ecx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEcx);

                        return;

                    case VirtualMachine::Reg::Edx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEdx);

                        return;

                    case VirtualMachine::Reg::Ebx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEbx);

                        return;

                    case VirtualMachine::Reg::Esp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEsp);

                        return;

                    case VirtualMachine::Reg::Ebp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEbp);

                        return;

                    case VirtualMachine::Reg::Esi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEsi);

                        return;
                    case VirtualMachine::Reg::Edi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushEdi);

                        return;

                    case VirtualMachine::Reg::Undefined:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::Nop);

                        return;
                }
            } else if (~rwMode.ram & ~rwMode.reg & rwMode.imm) {
                TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PushImm);
                TRANSLATE_IMM();

                return;
            } else {
                return;
            }

        case BytecodeInstruction::Opcode::pop:
            if (rwMode.ram & rwMode.reg & rwMode.imm) {
                switch (reg) {
                    case VirtualMachine::Reg::Eax:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEaxImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Ecx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEcxImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Edx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdxImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Ebx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEbxImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Esp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEspImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Ebp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEbpImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Esi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsiImmRam);
                        TRANSLATE_IMM();

                        return;
                    case VirtualMachine::Reg::Edi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdiImmRam);
                        TRANSLATE_IMM();

                        return;

                    case VirtualMachine::Reg::Undefined:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::Nop);

                        return;
                }
            } else if (rwMode.ram & rwMode.reg & ~rwMode.imm) {
                switch (reg) {
                    case VirtualMachine::Reg::Eax:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEaxRam);

                        return;

                    case VirtualMachine::Reg::Ecx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEcxRam);

                        return;

                    case VirtualMachine::Reg::Edx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdxRam);

                        return;

                    case VirtualMachine::Reg::Ebx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEbxRam);

                        return;

                    case VirtualMachine::Reg::Esp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEspRam);

                        return;

                    case VirtualMachine::Reg::Ebp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEbpRam);

                        return;

                    case VirtualMachine::Reg::Esi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsiRam);

                        return;
                    case VirtualMachine::Reg::Edi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdiRam);

                        return;

                    case VirtualMachine::Reg::Undefined:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::Nop);

                        return;
                }
            } else if (~rwMode.ram & rwMode.reg & ~rwMode.imm) {
                switch (reg) {
                    case VirtualMachine::Reg::Eax:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEax);

                        return;

                    case VirtualMachine::Reg::Ecx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEcx);

                        return;

                    case VirtualMachine::Reg::Edx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdx);

                        return;

                    case VirtualMachine::Reg::Ebx:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEbx);

                        return;

                    case VirtualMachine::Reg::Esp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsp);

                        return;

                    case VirtualMachine::Reg::Ebp:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEbp);

                        return;

                    case VirtualMachine::Reg::Esi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsi);

                        return;
                    case VirtualMachine::Reg::Edi:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdi);

                        return;

                    case VirtualMachine::Reg::Undefined:
                        TRANSLATE_PM_OPC(PhysicalMachine::Opcode::Nop);

                        return;
                }
            } else {
                return;
            }

        case BytecodeInstruction::Opcode::jmp:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::JmpRel);
            mcRelJmpInstrOperandAddrToPatch = mc->size();
            TRANSLATE_ADDR(-1);

        case BytecodeInstruction::Opcode::ja:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::CmpEsiEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::JaRel);
            mcRelJmpInstrOperandAddrToPatch = mc->size();
            TRANSLATE_ADDR(-1);

            return;

        case BytecodeInstruction::Opcode::jae:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::CmpEsiEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::JaeRel);
            mcRelJmpInstrOperandAddrToPatch = mc->size();
            TRANSLATE_ADDR(-1);

            return;

        case BytecodeInstruction::Opcode::jb:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::CmpEsiEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::JbRel);
            mcRelJmpInstrOperandAddrToPatch = mc->size();
            TRANSLATE_ADDR(-1);

            return;

        case BytecodeInstruction::Opcode::jbe:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::CmpEsiEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::JbeRel);
            mcRelJmpInstrOperandAddrToPatch = mc->size();
            TRANSLATE_ADDR(-1);

            return;

        case BytecodeInstruction::Opcode::je:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::CmpEsiEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::JeRel);
            mcRelJmpInstrOperandAddrToPatch = mc->size();
            TRANSLATE_ADDR(-1);

            return;

        case BytecodeInstruction::Opcode::jne:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEsi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::PopEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::CmpEsiEdi);
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::JneRel);
            mcRelJmpInstrOperandAddrToPatch = mc->size();
            TRANSLATE_ADDR(-1);

            return;

        case BytecodeInstruction::Opcode::call:
            TRANSLATE_PM_OPC(PhysicalMachine::Opcode::CallRel);
            mcRelJmpInstrOperandAddrToPatch = mc->size();
            TRANSLATE_ADDR(-1);

            return;

#undef TRANSLATE_VAL
#undef TRANSLATE_REL
#undef TRANSLATE_ADDR
#undef TRANSLATE_IMM
#undef TRANSLATE_PM_OPC
    }
}

void BytecodeInstruction::translateOpcToBack(std::vector<std::byte> *mc, PhysicalMachine::Opcode pmOpc)
{
    std::size_t opcSz = PhysicalMachine::opcSz(pmOpc);

    if (opcSz == 0) return;

    union {
        PhysicalMachine::Opcode pmOpc;
        std::byte bytes[3];
    } binary{.pmOpc = pmOpc};

    if (opcSz == 1)  {
        mc->emplace_back(binary.bytes[0]);
    } else if (opcSz == 2) {
        mc->emplace_back(binary.bytes[1]);
        mc->emplace_back(binary.bytes[0]);
    } else {
        mc->emplace_back(binary.bytes[2]);
        mc->emplace_back(binary.bytes[1]);
        mc->emplace_back(binary.bytes[0]);
    }
}

void BytecodeInstruction::translateImmToBack(std::vector<std::byte> *const mc, const Imm imm)
{
    union {
        Imm imm;
        std::byte bytes[sizeof(Imm)];
    } binary{.imm = imm};

    for (auto &byte: binary.bytes) mc->emplace_back(byte);
}

void BytecodeInstruction::translateImmToBack(std::vector<std::byte> *const mc) const
{
    translateImmToBack(mc, imm);
}

void BytecodeInstruction::translateImmToRelAddr(std::vector<std::byte> *mc, std::size_t relMcAddr, Imm imm)
{
    union {
        Imm imm;
        std::byte bytes[sizeof(Imm)];
    } binary{.imm = imm};

    for (std::size_t i = 0; i < sizeof(binary.bytes); ++i) mc->at(relMcAddr + i) = binary.bytes[i];
}

bool BytecodeInstruction::isJmp(const BytecodeInstruction bcInstr)
{
    return bcInstr.opcode == Opcode::jmp || bcInstr.opcode == Opcode::ja || bcInstr.opcode == Opcode::jae || bcInstr.opcode == Opcode::jb ||
           bcInstr.opcode == Opcode::jbe ||
           bcInstr.opcode == Opcode::je || bcInstr.opcode == Opcode::jne || bcInstr.opcode == Opcode::call;
}

std::size_t BytecodeInstruction::pmJmpInstrSz() const
{
    return (((opcode == Opcode::jmp) || (opcode == Opcode::call)) ? 1 : 6) + sizeof(Imm);
}
