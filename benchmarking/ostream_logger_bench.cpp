#include <PLODD/basic/ostream_logger.h>

#include <iostream>
#include <chrono>

using sc = std::chrono::steady_clock;
namespace c = std::chrono;
//Not null (that would terminate the string), but it is the same character, so acceptable?
const char * _64_null_str = "\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01"; 

unsigned int time_log_string(pld::base_logger * logger, int sample_size){
    sc::time_point start = sc::now();
    for(int i = 0; i <= sample_size; i++){
        logger->debug(_64_null_str);
    }
    sc::time_point end = sc::now();
    return c::duration_cast<c::nanoseconds>((end - start) / sample_size).count();
}

class null_stream : public std::ostream {
public:
  null_stream() : std::ostream(nullptr) {}
};

template <class T>
const null_stream &operator<<(null_stream &&os, const T &value) { 
  return os;
}

int main(){
    //-------------------BENCHMARKING_VARIABLES--------------------//
    null_stream null_stream;
    pld::ostream_logger test_logger(&null_stream, "Heyo", pld::level::DEBUG);
    int num_samples = 1000000;
    //------------------------BENCHMARKING-------------------------//
    std::cout << "//-------------------------------------------------------------//\n";
    std::cout << "// Commencing benchmark of ostream_logger with " << num_samples << " samples.\n";
    std::cout << "// Each sample (log) takes a 64 byte string and logs it to a null stream.\n";
    sc::time_point start = sc::now();
    int nano_secs_per_log = time_log_string(&test_logger, num_samples);
    sc::time_point end = sc::now();
    std::cout << "//  Total execution time (in seconds): " << c::duration_cast<c::seconds>(end - start).count() << " seconds.\n";
    std::cout << "//  Total execution time (in milliseconds): " << c::duration_cast<c::milliseconds>(end - start).count() << "ms.\n";
    std::cout << "//  Average log time: " << nano_secs_per_log << "ns\n";
    std::cout << "//-------------------------------------------------------------//\n";
}
