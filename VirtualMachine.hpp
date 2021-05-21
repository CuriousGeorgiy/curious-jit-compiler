#ifndef VIRTUAL_MACHINE_HPP
#define VIRTUAL_MACHINE_HPP

namespace VirtualMachine {
    enum class Reg {
        Undefined = -1,

        Eax,
        Ecx,
        Edx,
        Ebx,
        Esp,
        Ebp,
        Esi,
        Edi,
    };
}

#endif /* VIRTUAL_MACHINE_HPP */
