cmake_minimum_required(VERSION 3.0.0)

project(PLODD VERSION 0.0.0 LANGUAGES CXX)

option(BUILD_PLODD_EXAMPLE "Build the PLODD example code file." ON)
option(BUILD_PLODD_DOCS "Build the Doxygen PLODD documentation." OFF)
option(BUILD_PLODD_TESTS "Build and execute tests for PLODD" OFF)

set(lib_sources
    src/basic/base.cpp
	src/basic/both.cpp
	src/basic/console_logger.cpp
	src/basic/file_logger.cpp
	src/basic/multi_file_logger.cpp
	src/basic/single_file_logger.cpp
	src/basic/ostream_logger.cpp
	src/basic/uf_ostream_logger.cpp
)

if(BUILD_SHARED_LIBS)
	add_library(PLODD SHARED ${lib_sources})
	target_include_directories(PLODD PRIVATE include)
else()
	add_library(PLODD STATIC ${lib_sources})
	target_include_directories(PLODD PRIVATE include)
endif()

if(BUILD_PLODD_EXAMPLE)
	add_executable(PLODD_example src/example.cpp)
	target_include_directories(PLODD_example PRIVATE include)
	target_link_libraries(PLODD_example PLODD)
endif()

if(BUILD_PLODD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()

#BEFORE_RELEASE: Remove these options.
target_compile_options(PLODD
    PRIVATE "-Wextra"
    PRIVATE "-Werror"
)
if(BUILD_PLODD_EXAMPLE)
	target_compile_options(PLODD_example
		PRIVATE "-Wextra"
		PRIVATE "-Werror"
	)
endif()
