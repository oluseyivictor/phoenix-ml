add_library(${LIBRARY_NAME} STATIC 
    Matrix.cpp 
    Vector.cpp)
target_include_directories(${LIBRARY_NAME} PUBLIC 
    "../include"
    "${CMAKE_BINARY_DIR}/version_files/include/")