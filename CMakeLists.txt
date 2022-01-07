cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(vm VERSION 1.0 LANGUAGES CXX)

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
    -Wno-unused-parameter
    -Wno-unused-variable
    -Wno-unused-but-set-variable
    -Wno-float-equal
    -Wno-conversion
    -Wno-sign-conversion
    -Wno-sign-compare
    -Wno-sign-promo
    -Wno-old-style-cast
)

set(SRC ${PROJECT_SOURCE_DIR}/src/interpretator.cpp
        ${PROJECT_SOURCE_DIR}/src/loader.cpp
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${PROJECT_SOURCE_DIR}/src/types.cpp
        ${PROJECT_SOURCE_DIR}/src/types.cpp
)

execute_process(
    COMMAND python generator.py
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_subdirectory(assembler)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})
target_compile_features(${CMAKE_PROJECT_NAME} INTERFACE cxx_std_17)


target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)