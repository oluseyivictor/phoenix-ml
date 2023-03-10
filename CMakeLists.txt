cmake_minimum_required(VERSION 3.11.0)

project(
    Gherkins-ML
    VERSION 1.0.0
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD           17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)
set(CMAKE_CXX_EXTENSIONS         OFF)

set(LIBRARY_NAME Gherkin)
set(EXECUTABLE_NAME Executable)


include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
    GIT_SHALLOW TRUE
)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.2
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(googletest nlohmann_json)

option(COMPLE_EXECUTABLE "whether to compile the executable" OFF)

add_subdirectory(library)
add_subdirectory(app)
add_subdirectory(Test)