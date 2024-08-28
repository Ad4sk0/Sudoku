cmake_minimum_required(VERSION 3.10)

project(SudokuLibrary)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/sudoku)

file(GLOB_RECURSE SUDOKU_SOURCES "${SOURCE_DIR}/*.cpp")

add_library(SudokuLibrary STATIC ${SUDOKU_SOURCES})

target_include_directories(SudokuLibrary PUBLIC ${INCLUDE_DIR})

set_target_properties(SudokuLibrary PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
