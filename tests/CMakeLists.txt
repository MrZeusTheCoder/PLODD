cmake_minimum_required(VERSION 3.0.0)

include(CTest)

#Test file sources:
set(test_sources
    src/basic/base_test.cpp
    src/basic/ostream_logger_test.cpp
    src/ts/base_test.cpp
)

set(test_names
    tests.basic.base_test
    tests.basic.ostream_logger_test
    tests.ts.base_test
)


list(LENGTH test_sources num_test_sources)
math(EXPR lists_len "${num_test_sources} - 1")

foreach(index RANGE ${lists_len})
    #Variables:
    list(GET test_sources ${index} test_source)
    list(GET test_names ${index} test_name)
    #Make target and add target to ctest.
    add_executable(${test_name} ${test_source})
    add_test(NAME ${test_name} COMMAND ${test_name})
    #Configure target include dirs:
    target_include_directories(${test_name}
        PRIVATE ${PROJECT_SOURCE_DIR}/tests/include/ 
        PRIVATE ${PROJECT_SOURCE_DIR}/include/
    )
    #It's useless without PLODD, right?
    target_link_libraries(${test_name} PLODD)
endforeach(index RANGE ${lists_len})
