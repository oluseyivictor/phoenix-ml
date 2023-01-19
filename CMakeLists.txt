cmake_minimum_required(VERSION 3.0.0)

project(
    Gherkins-ML
    VERSION 1.0.0
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD           17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)
set(CMAKE_CXX_EXTENSIONS         OFF)

set(LIBRARY_NAME Gherkin)
set(EXECUTABLE_NAME Executable)

option(COMPLE_EXECUTABLE "whether to compile the executable" OFF)

add_subdirectory(library)
add_subdirectory(app)