cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(assembler VERSION 1.0 LANGUAGES CXX)



set(SRC ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${PROJECT_SOURCE_DIR}/src/assembler.cpp
        ${PROJECT_SOURCE_DIR}/src/loader.cpp
        ${PROJECT_SOURCE_DIR}/src/math_parser.cpp
)

add_executable(assembler ${SRC})
target_compile_features(assembler INTERFACE cxx_std_17)


target_include_directories(assembler PUBLIC ${PROJECT_SOURCE_DIR}/include)