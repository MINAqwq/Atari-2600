cmake_minimum_required(VERSION 3.12)

project(Atari6200-Emulator C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if (DEBUG)
    add_compile_definitions(ATARI_DEBUG)
endif ()

add_executable(atari2600
    src/bus/bus.c
    src/cpu/6507.c
    src/cpu/addressing.c
    src/cpu/instructions.c
    src/cpu/opcodes.c
    src/utils/debug.c
    src/atari2600.c
)

