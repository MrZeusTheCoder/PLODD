cmake_minimum_required(VERSION 3.0.0)

add_executable(ostream_benchmark ostream_logger_bench.cpp)
target_include_directories(ostream_benchmark PUBLIC ../include/)
target_link_libraries(ostream_benchmark PLODD)
set_target_properties(ostream_benchmark PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/PLODD/bin/benchmarking)