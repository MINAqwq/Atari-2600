cmake_minimum_required(VERSION 3.12)

project(Atari6200-Emulator C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(DEBUG)
    add_compile_definitions(ATARI_DEBUG)
endif()

add_executable(catari-2600
    src/bus/bus.c
    src/bus/memory_map.c
    src/cpu/6507.c
    src/cpu/addressing.c
    src/cpu/instructions.c
    src/cpu/opcodes.c
    src/utils/debug.c
    src/atari6200.c
)