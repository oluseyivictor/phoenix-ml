set(LIBRARY_SOURCES
    "Matrix.cpp"
    "Vector.cpp"
    "nn.cpp")

set(INCLUDE_HEADERS
    "../include/Matrix.h"
    "../include/Vector.h"
    "../include/nn.h")  
      
add_library(${LIBRARY_NAME} STATIC 
    ${LIBRARY_SOURCES}
    ${INCLUDE_HEADERS})

target_include_directories(${LIBRARY_NAME} PUBLIC 
    "../include"
    "${CMAKE_BINARY_DIR}/version_files/include/")

target_link_libraries(${LIBRARY_NAME} PUBLIC
    GTest::gtest_main
    nlohmann_json::nlohmann_json)
    