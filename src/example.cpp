#include <iostream>
#include <chrono>
#include <thread>

#include <PLODD/basic/file_logger.h>
#include <PLODD/basic/console_logger.h>
#include <PLODD/basic/collection.h>
#include <PLODD/basic/both.h>
#include <PLODD/basic/time.hpp>
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
    std::cout << "Pretend to do something while your boss is watching...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    pld::console.info("HEYO! This is a console info.");
    std::cout << "Twiddle your thumbs some more...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1300));
    pld::console.warn("HEYO! This is a console warn.");
    std::cout << "Claim you are waiting for some containers to spool up...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1700));
    pld::console.error("A fatal error occurred in boss::relationship::work. (This is a console error, by the way.)");
}

void test_both_logging(){
    pld::both.debug("HEYO! This is a debug log from the \"both\" logger, heh.");
    //1.2 seconds is the Golden Wait Time, trust me. Thousands of human hours have been wasted in market research.
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    pld::both.info("HEYO! This is a info log from the \"both\" logger, heh.");
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    pld::both.warn("HEYO! This is a warn log from the \"both\" logger, heh.");
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    pld::both.error("HEYO! This is a error log from the \"both\" logger, heh.");
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    pld::both.errorf("TWIST! Error {} That{}s {} Number of the day: 42. Date: {} (believe it or not). Also: NUMBERS! {}!", "log with formatting, :).", "'", "crazy, mon!", get_date(), 816.3264);
}


int main(){
    /*
    //BEFORE_NEXT_RELEASE: Add check for existence of directory and make if not there, THEN init file logger in there.
    pld::file.init_files("./test_logs/");
    std::cout << "Testing PLODD...\n";
    std::cout << "Testing file logger...\n";
    test_file_logging();
    test_console_logging();
    test_both_logging();
    */
}