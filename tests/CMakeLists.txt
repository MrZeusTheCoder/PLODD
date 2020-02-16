cmake_minimum_required(VERSION 3.0.0)

include(CTest)

#Test executable sources:
set(test_sources
    src/catch_main.cpp
    src/base_test.cpp
    src/ostream_logger_test.cpp
    src/uf_ostream_logger_test.cpp
)

#Test targets:
add_executable(PLODD_TEST_EXECUTABLE ${test_sources})
add_test(NAME PLODD_TESTS COMMAND PLODD_TEST_EXECUTABLE)

#Test executable target options:
target_include_directories(PLODD_TEST_EXECUTABLE
    PRIVATE ${PROJECT_SOURCE_DIR}/tests/include/ 
    PRIVATE ${PROJECT_SOURCE_DIR}/include/
)
target_link_libraries(PLODD_TEST_EXECUTABLE PLODD)