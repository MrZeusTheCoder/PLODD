//----------------------------------INCLUDES----------------------------------//
#include <iostream>
#include <chrono>
#include <thread>

#include <fmt/format.h>
#include <PLODD/basic/file_logger.h>
#include <PLODD/basic/console_logger.h>
#include <PLODD/basic/collection.h>
#include <PLODD/basic/both.h>
#include <PLODD/basic/time.hpp>
#include <PLODD/basic/ostream_logger.h>
#include <PLODD/basic/multi_file_logger.h>
//---------------------------------FUNCTIONS----------------------------------//
//TODO: Find a place for this filesystem code:
//Directory existence checker:
//////////////////////////////////////////////////////////////////////
/// @brief A platform independent directory existence checker.
/// @param path The path to what is assumed to be a directory or lack thereof.
/// @return true The directory exists!
/// @return false The directory doesn't exist!
//////////////////////////////////////////////////////////////////////
bool dir_exists(const std::string& path);
//Directory maker:
//////////////////////////////////////////////////////////////////////
/// @brief A platform independent directory maker.
/// @param path The path where the function attempts to make a directory.
/// @return true Making the directory succeeded.
/// @return false Making the directory failed.
//////////////////////////////////////////////////////////////////////
bool make_dir(const std::string& path);
//Platform dependent definitions:
#ifdef _WIN32
#include <windows.h>

bool dir_exists(const std::string& path){
    DWORD file_type = GetFileAttributesA(path.c_str());
    if (file_type == INVALID_FILE_ATTRIBUTES){
        return false; //The path is errornous.
    } else if (file_type & FILE_ATTRIBUTE_DIRECTORY){
        return true; //It is a directory!
    } else {
        return false; //It is just isn't a directory.
    }
}

bool make_dir(const std::string& path){
    if(CreateDirectory(path.c_str(), NULL)){
        return true;
    } else {
        return false;
    }
}
#else
#include <sys/stat.h>

bool dir_exists(const std::string& path){
    struct stat file_bitmask;
    if(stat(path.c_str(), &file_bitmask) == 0){ //The path exists, but is a a directory?
        if((file_bitmask.st_mode & S_IFDIR) != 0){ //It is a directory!
            return true;
        } else { //I don't know what it is, but sure isn't a directory.
            return false;
        }
    } else {
        return false; //The path doesn't even exist.
    }
}

bool make_dir(const std::string& path){
    if(mkdir(path.c_str(), (S_IRWXU | S_IRWXG | S_IRWXO))){
        return true;
    } else {
        return false;
    }
}
#endif

void multi_file_logger_logs(){
    pld::file.debug("HEYO! This is a file debug.");
    pld::file.info("HEYO! This is a file info.");
    pld::file.warn("HEYO! This is a file warn.");
    pld::file.error("HEYO! This is a file error.");
    pld::file.debugf("HEYO! This is a file debug, with a {}, check out the {} code {}. +{}", "twist", "source", "(src/example.cpp)", 1.314956); 
}

void sfl_example_logs(pld::single_file_logger& logger){
    logger.info("The file logger is set at the INFO logging level, so the following debug log won't be written:");
    logger.debug("HEYO! This is a file debug log.");
    logger.info("See... Don't trust me? Check the source code.");
    logger.info("HEYO! This is an information log, by the way.");
    logger.warn("This is a warning log.");
    logger.error("And this is an error log!");
    logger.infof("This is an info log, but with a {}. Check out the {} code {}. -{}", "twist", "source", "(src/example.cpp:sfl_example_logs)", 1.314956); 
}

void console_logger_logs(){
    pld::console.debug("HEYO! This is a console debug.");
    pld::console.info("HEYO! This is a console info.");
    pld::console.warn("HEYO! This is a console warn.");
    pld::console.error("HEYO! This is a console error.");
}

void both_logger_logs(){
    pld::both.debug("HEYO! This is a debug log from the \"both\" logger, fancy.");
    pld::both.info("HEYO! This is a info log from the \"both\" logger, newfound.");
    pld::both.warn("HEYO! This is a warn log from the \"both\" logger, impressive.");
    pld::both.error("HEYO! This is a error log from the \"both\" logger, triage.");
    pld::both.errorf("TWIST! Error {} That{}s {} Number of the day: 42. Date: {} (believe it or not). Also: NUMBERS! {}!", "log with formatting, :).", "'", "crazy, mon!", pld::get_date(), 816.3264);
}
//------------------------------------MAIN------------------------------------//
int main(){
    if(!dir_exists("./test_logs")){
        make_dir("./test_logs");
    }
    //Opens the files for logging:
    pld::file.init_files("./test_logs/");
    //All non-internal loggers must be constructed manually:
    pld::single_file_logger example_sf_logger("PLODD_SINGLE_FILE_LOGGER", pld::level::INFO);
    example_sf_logger.init_file("./test_logs/single_file.log");
    //
    std::cout << fmt::format("//{:-^80}//\n", "MULTI-FILE-LOGGING-EXAMPLE");
    std::cout << "Testing out the internally instantiated multi-file file logger (pld::file)...\n(Check the \"test_logs\" directory.)\n";
    multi_file_logger_logs();
    //
    std::cout << fmt::format("//{:-^80}//\n", "SINGLE-FILE-LOGGING-EXAMPLE");
    std::cout << "There isn't a built-in single file logger instance, so you have to instantiate your own.\n";
    std::cout << "Nonetheless, let's try it out.\n(Check the \"test_logs/single_file.log\")\n";
    sfl_example_logs(example_sf_logger);
    //
    std::cout << fmt::format("//{:-^80}//\n", "CONSOLE-LOGGING-EXAMPLE");
    std::cout << "The console logger is internally instantiated and can be accessed with pld::console.\n";
    std::cout << "Example:\n";
    console_logger_logs();
    //
    std::cout << fmt::format("//{:-^80}//\n", "BOTH-LOGGING-EXAMPLE");
    std::cout << "The \"both\" logger is basically an alias to both the internal file logger and console logger.\n";
    std::cout << "You can see it both right here in the console and in the multi-file logger's file(s).\n";
    std::cout << "See:\n";
    both_logger_logs();
}