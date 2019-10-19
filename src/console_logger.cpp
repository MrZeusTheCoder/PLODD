//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/console_logger.h".
//
/*----------------------------------INCLUDES----------------------------------*/
#include <PLODD/console_logger.h>

#include <iostream>

#include <PLODD/get_time.hpp>
#include <PLODD/fmt/format.h>
/*-------------------------------CONSOLE_LOGGER-------------------------------*/
namespace logging {

void console_logger::system_log(std::string msg){
    std::cout << colours::reverse_vid << "[" << get_time("%F %T") << "]:PLODD:INTERNAL_SYSTEM:" << msg << colours::reset << "\n";
}

console_logger::console_logger(std::string logger_name_, logging_level logging_level_) :
base_logger(logger_name_, logging_level_){
    std::cout << "Starting PLODD on " << get_time("%D") << " at " << get_time("%T") << "...\n";
}

void console_logger::set_level(logging_level new_level){
    logger_level = new_level;
}

void console_logger::set_name(std::string new_name){
    logger_name = new_name;
}

void console_logger::debug(std::string msg){
    #ifdef _WIN32
        //No ANSI support on Windows :(
        if(logger_level == logging_level::DEBUG){
            std::cout << "[" << get_time("%T") << "]:" << logger_name << ":DEBUG:" << msg << "\n";
        }
    #else
        if(logger_level == logging_level::DEBUG){
            std::cout << colours::gray << "[" << get_time("%T") << "]:" << logger_name << ":DEBUG:" << msg << colours::reset << "\n";
        }
    #endif
}

void console_logger::info(std::string msg){
    #ifdef _WIN32
        //No ANSI support on Windows :((
        if(logger_level <= logging_level::INFO){
            std::cout << "[" << get_time("%T") << "]:" << logger_name << ":INFO:" << msg << "\n";
        }
    #else
        if(logger_level <= logging_level::INFO){
            std::cout << colours::white << "[" << get_time("%T") << "]:" << logger_name << ":INFO:" << msg << colours::reset << "\n";
        }
    #endif
}
void console_logger::warn(std::string msg){
    #ifdef _WIN32
        //No ANSI support on Windows :(((
        if(logger_level <= logging_level::WARN){
            std::cout << "[" << get_time("%T") << "]:" << logger_name << ":WARN:" << msg << "\n";
        }
    #else
        if(logger_level <= logging_level::WARN){
            std::cout << colours::yellow << "[" << get_time("%T") << "]:" << logger_name << ":WARN:" << msg << colours::reset << "\n";
        }
    #endif
}
void console_logger::error(std::string msg){
    #ifdef _WIN32
        //No ANSI support on Windows (:()
        std::cout << "[" << get_time("%T") << "]:" << logger_name << ":ERROR:" << msg << "\n";
    #else
        std::cout << colours::red << "[" << get_time("%T") << "]:" << logger_name << ":ERROR:" << msg << colours::reset << "\n";
    #endif
}

console_logger console{"PLODD_CONSOLE", logging_level::INFO};

} //logging