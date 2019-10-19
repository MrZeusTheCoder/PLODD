#include <iostream>

#define PLODD_CUSTOM_NAMESPACE PLODD

#include <PLODD/file_logger.h>
#include <PLODD/console_logger.h>
#include <PLODD/collection.h>
#include <PLODD/both.h>
#include <PLODD/get_time.hpp>
#include <PLODD/stream_logger.h>

void test_file_logging(){
    logging::file.debug("HEYO! This is a file debug."); 
    logging::file.info("HEYO! This is a file info.");
    logging::file.warn("HEYO! This is a file warn.");
    logging::file.error("HEYO! This is a file error.");

    logging::file.debugf("HEYO! This is a file debug, with a {}, check out the {} code. +{}", "twist", "source", 1.314956); 
}

void test_console_logging(){
    logging::console.debug("HEYO! This is a console debug."); 
    logging::console.info("HEYO! This is a console info.");
    logging::console.warn("HEYO! This is a console warn.");
    logging::console.error("HEYO! This is a console error.");
}

void test_both_logging(){
    logging::both.debug("HEYO! This is a debug log from the \"both\" logger, heh.");
    logging::both.info("HEYO! This is a info log from the \"both\" logger, heh.");
    logging::both.warn("HEYO! This is a warn log from the \"both\" logger, heh.");
    logging::both.error("HEYO! This is a error log from the \"both\" logger, heh.");

    logging::both.errorf("Error {} that{}s {} Number of the day: 42. Date: {} (believe it or not). Also: NUMBERS: {}!", "log with a twist", "'", "crazy, mon!", get_time("%D"), 816.3264);
}

class A {};

int main(){
    /*
    logging::console_logger a("A", logging::level::DEBUG);
    logging::console_logger b("B", logging::level::DEBUG);
    logging::console_logger c("C", logging::level::DEBUG);
    logging::collection<logging::console_logger> abc{&a, &b, &c};
    logging::console_logger D("D", logging::level::DEBUG);
    logging::console_logger E("E", logging::level::DEBUG);
    logging::console_logger F("F", logging::level::DEBUG);
    logging::collection<logging::console_logger> def{&D, &E, &F};
    std::cout << "abc:\n";
    for(auto& x : abc){
        x->debug("HEY!");
    }
    std::cout << "def:\n";
    for(auto& x : def){
        x->debug("HEY!");
    }
	
    abc.swap(&def);

    std::cout << "abc:\n";
    for(auto& x : abc){
        x->debug("HEY!");
    }
    std::cout << "def:\n";
    for(auto& x : def){
        x->debug("HEY!");
    }
    */
    A foo;
    logging::stream_logger<std::ostream, true> a(&std::cout, "A", logging::level::DEBUG);
    a.debug("HEYO!");
    exit(0);
    
    
    //BEFORE_NEXT_RELEASE: Add check for existence of directory and make if not there, THEN init file logger in there.
    logging::file.init_files("./test_logs/");
	std::cout << "Testing PLODD...\n";
	std::cout << "Testing file logger...\n";
	test_file_logging();
	std::cout << "Testing console logger...\n";
	test_console_logging();
	std::cout << "Testing \"both\" logger...\n";
	test_both_logging();
}
