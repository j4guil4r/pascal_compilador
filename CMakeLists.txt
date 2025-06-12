cmake_minimum_required(VERSION 3.30)
project(pascal_compilador)

set(CMAKE_CXX_STANDARD 26)

add_executable(pascal_compilador main.cpp
        src/tokens/token.h
        src/tokens/token.cpp
        src/scanner/scanner.h
        src/scanner/scanner.cpp
        src/ast/exp.h
        src/visitors/visitor.h
        src/ast/stmt.h
        src/ast/program.h
        src/ast/exp.cpp
        src/ast/stmt.cpp
        src/enviroment/enviroment.h)
