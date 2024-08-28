cmake_minimum_required(VERSION 3.10)
project(SudokuGUI)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)

include_directories(${CMAKE_SOURCE_DIR}/sudoku/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

add_executable(SudokuGUI ${SOURCES} ${HEADERS})

set(RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/Roboto-Regular.ttf)

source_group("Resources" FILES ${RESOURCE_FILES})

add_custom_command(TARGET SudokuGUI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:SudokuGUI>/resources
)

target_link_libraries(SudokuGUI  PRIVATE SudokuLibrary sfml-graphics)
target_compile_features(SudokuGUI  PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET SudokuGUI 
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:SudokuGUI>
        VERBATIM)
endif()