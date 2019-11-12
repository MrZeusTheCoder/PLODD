#include <iostream>

#define PLODD_CUSTOM_NAMESPACE PLODD

#include <PLODD/file_logger.h>
#include <PLODD/console_logger.h>
#include <PLODD/collection.h>
#include <PLODD/both.h>
#include <PLODD/get_time.hpp>

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

class A {
    private:
        std::string latest_msg;
    public:
        void operator<<(std::string& msg){ latest_msg = msg; }
        void print_latest_msg(){ std::cout << latest_msg; }
};


int main(){
    
    
    
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
