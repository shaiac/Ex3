cmake_minimum_required(VERSION 3.15)
project(ex3)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex3 main.cpp commands.h commands.cpp symbolTable.h symbolTable.cpp commandsControl.h commandsControl.cpp ex1.cpp lexer.cpp Expression.h singeltonInter.h singeltonInter.cpp)