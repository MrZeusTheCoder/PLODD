cmake_minimum_required(VERSION 3.0.0)

#BEFORE_RELEASE: Set the version!
project(PLODD VERSION 0.0.0 LANGUAGES CXX)

########################################
#         PLODD BUILD OPTIONS          #
########################################
option(PLODD_BUILD_EXAMPLE "Build the PLODD example code file." ON)
option(PLODD_BUILD_DOCS "Build the Doxygen PLODD documentation." OFF)
option(PLODD_BUILD_TESTS "Build tests for PLODD" OFF)
option(PLODD_BUILD_BENCHMARKS "Build benchmarks for some PLODD classes" OFF)

########################################
#      PLODD MODULAR BUILD SYSTEM      #
########################################
# PLODD has a very unique build system that allows it to be built
# with non-essential source files missing. This means if you remove
# an unneeded (but unessential) header file the source will file 
# for that header won't even be compiled! (the reverse is also true) 
# This allows for more customization then ever before.
#
# All that's required by you to try it out is deleting a few files
# and seeing what happens!
########################################
#...

#The PLODD's sources CMake will attempt to build:
set(lib_sources)

#Aliases for the source paths.
set(inc_pth ${PROJECT_SOURCE_DIR}/include/PLODD)
set(src_pth ${PROJECT_SOURCE_DIR}/src)

#Build thread-safe modules?
if(EXISTS "${inc_pth}/ts")
	set(build_ts_modules true)
else()
	set(build_ts_modules false)
endif()

#Required files for PLODD to build.
set(required_modules)

set(required_basic_modules
	${inc_pth}/basic/base.h
	${inc_pth}/basic/time.hpp
	${src_pth}/basic/base.cpp
)
set(required_ts_modules
	${inc_pth}/ts/time.hpp
)

list(APPEND required_modules ${required_basic_modules})
if(build_ts_modules)
	list(APPEND required_modules ${required_ts_modules})
endif()

#Check for required sources (and fail build if they don't exist):
foreach(required_file ${required_modules})
	if(EXISTS "${required_file}")
		continue()
	else()
		message(FATAL_ERROR "Your PLODD filesystem is lacking a file essential to building PLODD: ${required_file} (Maybe you didn't remove the (optional) directory it was supposed to be in.)")
	endif()
endforeach(required_file ${required_modules})

#All is safe now...
list(APPEND lib_sources ${required_modules})

#Non-essential, but build-able modules. (The required modules have already been added to the source list.)
set(extra_modules)
set(basic_modules
	basic/both
	basic/console_logger
	basic/collection
	basic/file_logger
	basic/multi_file_logger
	basic/single_file_logger
	basic/ostream_logger
	basic/uf_ostream_logger
)
set(thread_safe_modules
	ts/ostream_logger
)

list(APPEND extra_modules ${basic_modules})
if(build_ts_modules)
	list(APPEND extra_modules ${thread_safe_modules})
endif()

foreach(module ${extra_modules})
	if(EXISTS "${inc_pth}/${module}.h" AND EXISTS "${src_pth}/${module}.cpp")
		list(APPEND lib_sources "${src_pth}/${module}.cpp")
	endif()
endforeach(module ${extra_modules})

########################################
function(add_warnings target)
	target_compile_options(${target} PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror
			-Wall
			-Wextra
		>
		$<$<CXX_COMPILER_ID:MSVC>:
			/WX
			/W3
		>
	)
endfunction(add_warnings target)



########################################
#            BUILD TARGETS             #
########################################

if(BUILD_SHARED_LIBS)
	add_library(PLODD SHARED ${lib_sources})
	target_compile_definitions(PLODD PRIVATE -DPLODD_SHARED -DPLODD_EXPORT_API)
else()
	add_library(PLODD STATIC ${lib_sources})
	target_compile_definitions(PLODD PRIVATE -DPLODD_STATIC)
endif()

target_include_directories(PLODD PRIVATE include)
target_compile_features(PLODD PUBLIC cxx_std_11)
add_warnings(PLODD)
set_target_properties(PLODD PROPERTIES ENABLE_EXPORTS ON)
set_target_properties(PLODD PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/PLODD/lib)

if(PLODD_BUILD_EXAMPLE)
	add_executable(PLODD_example src/example.cpp)
	target_include_directories(PLODD_example PRIVATE include)
	target_link_libraries(PLODD_example PLODD)
	add_warnings(PLODD_example)
	set_target_properties(PLODD_example PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/PLODD/bin)
endif()

if(PLODD_BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()

if(PLODD_BUILD_BENCHMARKS)
	add_subdirectory(benchmarking)
endif()

