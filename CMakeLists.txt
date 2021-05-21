cmake_minimum_required(VERSION 3.16)
project(curious-jit-compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -m32 -no-pie -march=i386")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32 -fno-plt -fno-pie -march=i386")

add_executable(curious-jit VirtualMachine.hpp)
target_sources(curious-jit PUBLIC CompilationEngineMain.cpp CompilationEngine.cpp BytecodeInstruction.cpp PhysicalMachine.cpp)
target_include_directories(curious-jit PUBLIC "${PROJECT_SOURCE_DIR}")

add_executable(assembler)
target_sources(assembler PUBLIC AssemblerMain.cpp Assembler.cpp File.cpp Text.cpp)
target_include_directories(assembler PUBLIC "${PROJECT_SOURCE_DIR}")

add_executable(disassembler)
target_sources(disassembler PUBLIC DisassemblerMain.cpp Disassembler.cpp File.cpp)
target_include_directories(disassembler PUBLIC "${PROJECT_SOURCE_DIR}")
