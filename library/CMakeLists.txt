add_subdirectory(src)

configure_file(
    "config.hpp.in"
    "${CMAKE_BINARY_DIR}/version_files/include/config.hpp" ESCAPE_QUOTES
)