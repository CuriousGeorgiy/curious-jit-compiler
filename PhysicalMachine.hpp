#ifndef MACHINE_CODE_HPP
#define MACHINE_CODE_HPP

#include <cstddef>

namespace PhysicalMachine {
    enum class Opcode {
        Undefined = -1,

        /* push r */
        PushEax = 0x50,
        PushEcx = 0x51,
        PushEdx = 0x52,
        PushEbx = 0x53,
        PushEsp = 0x54,
        PushEbp = 0x55,
        PushEsi = 0x56,
        PushEdi = 0x57,

        /* pop r */
        PopEax = 0x58,
        PopEcx = 0x59,
        PopEdx = 0x5a,
        PopEbx = 0x5b,
        PopEsp = 0x5c,
        PopEbp = 0x5d,
        PopEsi = 0x5e,
        PopEdi = 0x5f,

        /* push [r + imm] */
        PushEaxImmRam = 0xffb0,
        PushEcxImmRam = 0xffb1,
        PushEdxImmRam = 0xffb2,
        PushEbxImmRam = 0xffb3,
        PushEspImmRam = 0xffb424,
        PushEbpImmRam = 0xffb5,
        PushEsiImmRam = 0xffb6,
        PushEdiImmRam = 0xffb7,

        /* push [r] */
        PushEaxRam = 0xff30,
        PushEcxRam = 0xff31,
        PushEdxRam = 0xff32,
        PushEbxRam = 0xff33,
        PushEspRam = 0xff34,
        PushEbpRam = 0xff35,
        PushEsiRam = 0xff36,
        PushEdiRam = 0xff37,

        /* pop [r + imm] */
        PopEaxImmRam = 0x8f80,
        PopEcxImmRam = 0x8f81,
        PopEdxImmRam = 0x8f82,
        PopEbxImmRam = 0x8f83,
        PopEspImmRam = 0x8f84,
        PopEbpImmRam = 0x8f85,
        PopEsiImmRam = 0x8f86,
        PopEdiImmRam = 0x8f87,

        /* pop [r] */
        PopEaxRam = 0x8f00,
        PopEcxRam = 0x8f01,
        PopEdxRam = 0x8f02,
        PopEbxRam = 0x8f03,
        PopEspRam = 0x8f04,
        PopEbpRam = 0x8f05,
        PopEsiRam = 0x8f06,
        PopEdiRam = 0x8f07,

        /* push imm */
        PushImm = 0x68,

        /* nop */
        Nop = 0x90,

        /* jmp imm ; relative */
        JmpRel = 0xe9,
        JaRel = 0x0f87,
        JaeRel = 0x0f83,
        JbRel = 0x0f82,
        JbeRel = 0x0f86,
        JeRel = 0x0f84,
        JneRel = 0x0f85,

        /* call imm ; relative */
        CallRel = 0xe8,

        /* ret */
        Ret = 0xc3,

        /* mov r, eax */
        MovEaxEax = 0x89c0,
        MovEaxEcx = 0x89c1,
        MovEaxEdx = 0x89c2,
        MovEaxEbx = 0x89c3,
        MovEaxEsp = 0x89c4,
        MovEaxEbp = 0x89c5,
        MovEaxEsi = 0x89c6,
        MovEaxEdi = 0x89c7,

        /* mov r, ecx */
        MovEcxEax = 0x89c8,
        MovEcxEcx = 0x89c9,
        MovEcxEdx = 0x89ca,
        MovEcxEbx = 0x89cb,
        MovEcxEbp = 0x89cd,
        MovEcxEsi = 0x89ce,
        MovEcxEdi = 0x89cf,

        /* mov r, edx */
        MovEdxEax = 0x89d0,
        MovEdxEcx = 0x89d1,
        MovEdxEdx = 0x89d2,
        MovEdxEbx = 0x89d3,
        MovEdxEbp = 0x89d5,
        MovEdxEsi = 0x89d6,
        MovEdxEdi = 0x89d7,

        /* mov r, ebx */
        MovEbxEax = 0x89d8,
        MovEbxEcx = 0x89d9,
        MovEbxEdx = 0x89da,
        MovEbxEbx = 0x89db,
        MovEbxEbp = 0x89dd,
        MovEbxEsi = 0x89de,
        MovEbxEdi = 0x89df,

        /* mov r, esp */
        MovEspEax = 0x89e0,

        /* mov r, ebp */
        MovEbpEax = 0x89e8,
        MovEbpEcx = 0x89e9,
        MovEbpEdx = 0x89ea,
        MovEbpEbx = 0x89eb,
        MovEbpEbp = 0x89ed,
        MovEbpEsi = 0x89ee,
        MovEbpEdi = 0x89ef,

        /* mov r, esi */
        MovEsiEax = 0x89f0,
        MovEsiEcx = 0x89f1,
        MovEsiEdx = 0x89f2,
        MovEsiEbx = 0x89f3,
        MovEsiEbp = 0x89f5,
        MovEsiEsi = 0x89f6,
        MovEsiEdi = 0x89f7,

        /* mov r, edi */
        MovEdiEax = 0x89f8,
        MovEdiEcx = 0x89f9,
        MovEdiEdx = 0x89fa,
        MovEdiEbx = 0x89fb,
        MovEdiEbp = 0x89fd,
        MovEdiEsi = 0x89fe,
        MovEdiEdi = 0x89ff,

        /* mov r, imm */
        MovEax = 0xb8,
        MovEcx = 0xb9,
        MovEdi = 0xbf,
        MovEdx = 0xba,
        MovEbx = 0xbb,
        MovEbp = 0xbd,
        MovEsi = 0xbe,

        /* mov [imm], r */
        MovRamEbx = 0x891d,
        MovRamEsp = 0x8925,
        MovRamEbp = 0x892d,
        MovRamEsi = 0x8935,
        MovRamEdi = 0x893d,

        /* mov r, [imm]*/
        MovEbxRam = 0x8b1d,
        MovEspRam = 0x8b25,
        MovEbpRam = 0x8b2d,
        MovEsiRam = 0x8b35,
        MovEdiRam = 0x8b3d,

        /* add r, eax */
        AddEaxEax = 0x01c0,
        AddEcxEax = 0x01c1,
        AddEdxEax = 0x01c2,
        AddEbxEax = 0x01c3,
        AddEbpEax = 0x01c5,
        AddEsiEax = 0x01c6,
        AddEdiEax = 0x01c7,

        /* add r, ecx */
        AddEaxEcx = 0x01c8,
        AddEcxEcx = 0x01c9,
        AddEdxEcx = 0x01ca,
        AddEbxEcx = 0x01cb,
        AddEbpEcx = 0x01cd,
        AddEsiEcx = 0x01ce,
        AddEdiEcx = 0x01cf,

        /* add r, edx */
        AddEaxEdx = 0x01d0,
        AddEcxEdx = 0x01d1,
        AddEdxEdx = 0x01d2,
        AddEbxEdx = 0x01d3,
        AddEbpEdx = 0x01d5,
        AddEsiEdx = 0x01d6,
        AddEdiEdx = 0x01d7,

        /* add r, ebx */
        AddEaxEbx = 0x01d8,
        AddEcxEbx = 0x01d9,
        AddEdxEbx = 0x01da,
        AddEbxEbx = 0x01db,
        AddEbpEbx = 0x01dd,
        AddEsiEbx = 0x01de,
        AddEdiEbx = 0x01df,

        /* add r, ebp */
        AddEaxEbp = 0x01e8,
        AddEcxEbp = 0x01e9,
        AddEdxEbp = 0x01ea,
        AddEbxEbp = 0x01eb,
        AddEbpEbp = 0x01ed,
        AddEsiEbp = 0x01ee,
        AddEdiEbp = 0x01ef,

        /* add r, esi */
        AddEaxEsi = 0x01f0,
        AddEcxEsi = 0x01f1,
        AddEdxEsi = 0x01f2,
        AddEbxEsi = 0x01f3,
        AddEbpEsi = 0x01f5,
        AddEsiEsi = 0x01f6,
        AddEdiEsi = 0x01f7,

        /* add r, edi */
        AddEaxEdi = 0x01f8,
        AddEcxEdi = 0x01f9,
        AddEdxEdi = 0x01fa,
        AddEbxEdi = 0x01fb,
        AddEbpEdi = 0x01fd,
        AddEsiEdi = 0x01fe,
        AddEdiEdi = 0x01ff,

        /* sub r, eax */
        SubEaxEax = 0x2bc0,
        SubEaxEcx = 0x2bc1,
        SubEaxEdx = 0x2bc2,
        SubEaxEbx = 0x2bc3,
        SubEaxEbp = 0x2bc5,
        SubEaxEsi = 0x2bc6,
        SubEaxEdi = 0x2bc7,

        /* sub r, ecx */
        SubEcxEax = 0x2bc8,
        SubEcxEcx = 0x2bc9,
        SubEcxEdx = 0x2bca,
        SubEcxEbx = 0x2bcb,
        SubEcxEbp = 0x2bcd,
        SubEcxEsi = 0x2bce,
        SubEcxEdi = 0x2bcf,

        /* sub r, edx */
        SubEdxEax = 0x2bd0,
        SubEdxEcx = 0x2bd1,
        SubEdxEdx = 0x2bd2,
        SubEdxEbx = 0x2bd3,
        SubEdxEbp = 0x2bd5,
        SubEdxEsi = 0x2bd6,
        SubEdxEdi = 0x2bd7,

        /* sub r, ebx*/
        SubEbxEax = 0x2bd8,
        SubEbxEcx = 0x2bd9,
        SubEbxEdx = 0x2bda,
        SubEbxEbx = 0x2bdb,
        SubEbxEbp = 0x2bdd,
        SubEbxEsi = 0x2bde,
        SubEbxEdi = 0x2bdf,

        /* sub r, epb */
        SubEbpEax = 0x2be8,
        SubEbpEcx = 0x2be9,
        SubEbpEdx = 0x2bea,
        SubEbpEbx = 0x2beb,
        SubEbpEbp = 0x2bed,
        SubEbpEsi = 0x2bee,
        SubEbpEdi = 0x2bef,

        /* sub r, esi */
        SubEsiEax = 0x2bf0,
        SubEsiEcx = 0x2bf1,
        SubEsiEdx = 0x2bf2,
        SubEsiEbx = 0x2bf3,
        SubEsiEbp = 0x2bf5,
        SubEsiEsi = 0x2bf6,
        SubEsiEdi = 0x2bf7,

        /* sub r, edi */
        SubEdiEax = 0x2bf8,
        SubEdiEcx = 0x2bf9,
        SubEdiEdx = 0x2bfa,
        SubEdiEbx = 0x2bfb,
        SubEdiEbp = 0x2bfd,
        SubEdiEsi = 0x2bfe,
        SubEdiEdi = 0x2bff,

        /* cmp r, eax */
        CmpEaxEax = 0x39c0,
        CmpEcxEax = 0x39c1,
        CmpEdxEax = 0x39c2,
        CmpEbxEax = 0x39c3,
        CmpEbpEax = 0x39c5,
        CmpEsiEax = 0x39c6,
        CmpEdiEax = 0x39c7,

        /* cmp r, ecx */
        CmpEaxEcx = 0x39c8,
        CmpEcxEcx = 0x39c9,
        CmpEdxEcx = 0x39ca,
        CmpEbxEcx = 0x39cb,
        CmpEbpEcx = 0x39cd,
        CmpEsiEcx = 0x39ce,
        CmpEdiEcx = 0x39cf,

        /* cmp r, edx */
        CmpEaxEdx = 0x39d0,
        CmpEcxEdx = 0x39d1,
        CmpEdxEdx = 0x39d2,
        CmpEbxEdx = 0x39d3,
        CmpEbpEdx = 0x39d5,
        CmpEsiEdx = 0x39d6,
        CmpEdiEdx = 0x39d7,

        /* cmp r, ebx */
        CmpEaxEbx = 0x39d8,
        CmpEcxEbx = 0x39d9,
        CmpEdxEbx = 0x39da,
        CmpEbxEbx = 0x39db,
        CmpEbpEbx = 0x39dd,
        CmpEsiEbx = 0x39de,
        CmpEdiEbx = 0x39df,

        /* cmp r, ebp */
        CmpEaxEbp = 0x39e8,
        CmpEcxEbp = 0x39e9,
        CmpEdxEbp = 0x39ea,
        CmpEbxEbp = 0x39eb,
        CmpEbpEbp = 0x39ed,
        CmpEsiEbp = 0x39ee,
        CmpEdiEbp = 0x39ef,

        /* cmp r, esi */
        CmpEaxEsi = 0x39f0,
        CmpEcxEsi = 0x39f1,
        CmpEdxEsi = 0x39f2,
        CmpEbxEsi = 0x39f3,
        CmpEbpEsi = 0x39f5,
        CmpEsiEsi = 0x39f6,
        CmpEdiEsi = 0x39f7,

        /* cmp r, edi */
        CmpEaxEdi = 0x39f8,
        CmpEcxEdi = 0x39fb,
        CmpEdxEdi = 0x39fa,
        CmpEbxEdi = 0x39f9,
        CmpEbpEdi = 0x39fd,
        CmpEsiEdi = 0x39fe,
        CmpEdiEdi = 0x39ff,

        /* add r, imm */
        AddEax = 0x81c0,
        AddEcx = 0x81c1,
        AddEdx = 0x81c2,
        AddEbx = 0x81c3,
        AddEsp = 0x81c4,
        AddEbp = 0x81c5,
        AddEsi = 0x81c6,
        AddEdi = 0x81c7,

        /* sub r, imm */
        SubEax = 0x81e8,
        SubEcx = 0x81e9,
        SubEdx = 0x81ea,
        SubEbx = 0x81eb,
        SubEsp = 0x81ec,
        SubEbp = 0x81ed,
        SubEsi = 0x81ee,
        SubEdi = 0x81ef,

        /* cmp eax, imm */
        CmpEax = 0x81f8,
        CmpEcx = 0x81f9,
        CmpEdx = 0x81fa,
        CmpEbx = 0x81fb,
        CmpEbp = 0x81fd,
        CmpEsi = 0x81fe,
        CmpEdi = 0x81ff,

        /* mul r ; edx:eax := eax * r */
        MulEax = 0xf7e0,
        MulEcx = 0xf7e1,
        MulEdx = 0xf7e2,
        MulEbx = 0xf7e3,
        MulEbp = 0xf7e5,
        MulEsi = 0xf7e6,
        MulEdi = 0xf7e7,

        /* div r ; eax = edx:eax / r, edx := edx:eax % r */
        DivEax = 0xf7f0,
        DivEcx = 0xf7f1,
        DivEdx = 0xf7f2,
        DivEbx = 0xf7f3,
        DivEbp = 0xf7f5,
        DivEsi = 0xf7f6,
        DivEdi = 0xf7f7,

        /* xor eax, r */
        XorEaxEax = 0x33c0,
        XorEaxEcx = 0x33c1,
        XorEaxEdx = 0x33c2,
        XorEaxEbx = 0x33c3,
        XorEaxEbp = 0x33c5,
        XorEaxEsi = 0x33c6,
        XorEaxEdi = 0x33c7,

        /* xor ecx, r */
        XorEcxEax = 0x33c8,
        XorEcxEcx = 0x33c9,
        XorEcxEdx = 0x33ca,
        XorEcxEbx = 0x33cb,
        XorEcxEbp = 0x33cd,
        XorEcxEsi = 0x33ce,
        XorEcxEdi = 0x33cf,

        /* xor edx, r */
        XorEdxEax = 0x33d0,
        XorEdxEcx = 0x33d1,
        XorEdxEdx = 0x33d2,
        XorEdxEbx = 0x33d3,
        XorEdxEbp = 0x33d5,
        XorEdxEsi = 0x33d6,
        XorEdxEdi = 0x33d7,

        /* xor ebx, r */
        XorEbxEax = 0x33d8,
        XorEbxEcx = 0x33d9,
        XorEbxEdx = 0x33da,
        XorEbxEbx = 0x33db,
        XorEbxEbp = 0x33dd,
        XorEbxEsi = 0x33de,
        XorEbxEdi = 0x33df,

        /* xor ebp, r */
        XorEbpEax = 0x33e8,
        XorEbpEcx = 0x33e9,
        XorEbpEdx = 0x33ea,
        XorEbpEbx = 0x33eb,
        XorEbpEbp = 0x33ed,
        XorEbpEsi = 0x33ee,
        XorEbpEdi = 0x33ef,

        /* xor esi, r */
        XorEsiEax = 0x33f0,
        XorEsiEcx = 0x33f1,
        XorEsiEdx = 0x33f2,
        XorEsiEbx = 0x33f3,
        XorEsiEbp = 0x33f5,
        XorEsiEsi = 0x33f6,
        XorEsiEdi = 0x33f7,

        /* xor edi, r */
        XorEdiEax = 0x33f8,
        XorEdiEcx = 0x33f9,
        XorEdiEdx = 0x33fa,
        XorEdiEbx = 0x33fb,
        XorEdiEbp = 0x33fd,
        XorEdiEsi = 0x33fe,
        XorEdiEdi = 0x33ff,

        /* XOR r, imm */
        XorEax = 0x81f0,
        XorEcx = 0x81f1,
        XorEdx = 0x81f2,
        XorEbx = 0x81f3,
        XorEbp = 0x81f5,
        XorEsi = 0x81f6,
        XorEdi = 0x81f7,
    };

    constexpr std::size_t opcSz(Opcode opc) {
        switch (opc) {
            case Opcode::Undefined:
                return 0;

            case Opcode::PushEax:
            case Opcode::PushEcx:
            case Opcode::PushEdx:
            case Opcode::PushEbx:
            case Opcode::PushEsp:
            case Opcode::PushEbp:
            case Opcode::PushEsi:
            case Opcode::PushEdi:
            case Opcode::PopEax:
            case Opcode::PopEcx:
            case Opcode::PopEdx:
            case Opcode::PopEbx:
            case Opcode::PopEsp:
            case Opcode::PopEbp:
            case Opcode::PopEsi:
            case Opcode::PopEdi:
            case Opcode::MovEax:
            case Opcode::MovEcx:
            case Opcode::MovEdi:
            case Opcode::MovEdx:
            case Opcode::MovEbx:
            case Opcode::MovEbp:
            case Opcode::MovEsi:
            case Opcode::PushImm:
            case Opcode::Nop:
            case Opcode::JmpRel:
            case Opcode::CallRel:
            case Opcode::Ret:
                return 1;

            case Opcode::PushEspImmRam:
                return 3;

            default:
                return 2;
        }
    }
}

#endif /* MACHINE_CODE_HPP */
