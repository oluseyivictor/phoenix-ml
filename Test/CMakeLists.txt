if(ENABLE_TESTING)

    set(TEST_SOURCES
        "test.cpp")

    add_executable(testRunner  ${TEST_SOURCES} )
    target_link_libraries(testRunner ${LIBRARY_NAME})

endif()