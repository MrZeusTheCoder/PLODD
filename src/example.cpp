#include <iostream>

#include <PLODD/basic/file_logger.h>
#include <PLODD/basic/console_logger.h>
#include <PLODD/basic/collection.h>
#include <PLODD/basic/both.h>
#include <PLODD/time.hpp>
#include <PLODD/basic/ostream_logger.h>

void test_file_logging(){
    pld::file.debug("HEYO! This is a file debug."); 
    pld::file.info("HEYO! This is a file info.");
    pld::file.warn("HEYO! This is a file warn.");
    pld::file.error("HEYO! This is a file error.");

    pld::file.debugf("HEYO! This is a file debug, with a {}, check out the {} code. +{}", "twist", "source", 1.314956); 
}

void test_console_logging(){
    pld::console.debug("HEYO! This is a console debug."); 
    pld::console.info("HEYO! This is a console info.");
    pld::console.warn("HEYO! This is a console warn.");
    pld::console.error("HEYO! This is a console error.");
}

void test_both_logging(){
    pld::both.debug("HEYO! This is a debug log from the \"both\" logger, heh.");
    pld::both.info("HEYO! This is a info log from the \"both\" logger, heh.");
    pld::both.warn("HEYO! This is a warn log from the \"both\" logger, heh.");
    pld::both.error("HEYO! This is a error log from the \"both\" logger, heh.");

    pld::both.errorf("Error {} that{}s {} Number of the day: 42. Date: {} (believe it or not). Also: NUMBERS: {}!", "log with a twist", "'", "crazy, mon!", get_date(), 816.3264);
}

#include <chrono>
using sc = std::chrono::steady_clock;
namespace c = std::chrono;

const char * _64_null_str = "\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x00"; 

unsigned int time_log_string(pld::base_logger * logger, int sample_size){
    sc::time_point start = sc::now();
    for(int i = 0; i <= sample_size; i++){
        logger->debug(_64_null_str);
    }
    sc::time_point end = sc::now();
    return c::duration_cast<c::nanoseconds>((end - start) / sample_size).count();
}

class NullStream : public std::ostream {
public:
  NullStream() : std::ostream(nullptr) {}
  //NullStream(const NullStream &) : std::ostream(nullptr) {}
};

template <class T>
const NullStream &operator<<(NullStream &&os, const T &value) { 
  return os;
}

int main(){
    /*
    //BEFORE_NEXT_RELEASE: Add check for existence of directory and make if not there, THEN init file logger in there.
    pld::file.init_files("./test_logs/");
    std::cout << "Testing PLODD...\n";
    std::cout << "Testing file logger...\n";
    test_file_logging();
    */
    NullStream null_stream;
    pld::ostream_logger test_logger(&null_stream, "Heyo", pld::level::DEBUG);
    int num_samples = 800000;
    std::cout << "Average log time (over " << num_samples << " samples): " << time_log_string(&test_logger, num_samples) << "ns\n";	
    /*
    std::cout << "Testing \"both\" logger...\n";
    test_both_logging();
    */
}