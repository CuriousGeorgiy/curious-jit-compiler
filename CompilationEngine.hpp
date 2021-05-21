#ifndef COMPILATION_ENGINE_HPP
#define COMPILATION_ENGINE_HPP

#include <cstddef>
#include <cstdint>
#include <cinttypes>

#include <stack>
#include <string>
#include <vector>

#include "BytecodeInstruction.hpp"
#include "PhysicalMachine.hpp"
#include "ReadWrite.hpp"

class CompilationEngine final {
public:
    explicit CompilationEngine(const char *bcFileName);

    void run() const;

    static constexpr const char *const printFmt = "%" PRId32 "\n";
    static constexpr const char *const scanFmt = "%" PRId32;
    static Imm scanVal;
    static Imm ebx, esp, ebp, esi, edi;

private:
    void parse(const char *bc, std::size_t sz);
    void translate();

    std::vector<BytecodeInstruction> bcInstrs;
    std::vector<std::byte> mc;

};

#endif /* COMPILATION_ENGINE_HPP */
