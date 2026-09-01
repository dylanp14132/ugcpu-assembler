cmake_minimum_required(VERSION 3.10)
project(ugcpu_assembler LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_executable(ugcpu_assembler
        main.c
        opcodes.c opcodes.h
        parser.h  parser.c
)
