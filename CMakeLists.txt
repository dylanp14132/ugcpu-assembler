cmake_minimum_required(VERSION 3.10)
project(ugcpu_assembler LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(ugcpu_assembler
        src/main.c
        include/opcodes.h src/opcodes.c
        include/parser.h src/parser.c
)

target_include_directories(ugcpu_assembler PRIVATE include)