//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/both.h".
//
/*----------------------------------INCLUDES----------------------------------*/
#include <PLODD/both.h>

#include <PLODD/get_time.hpp>
/*------------------------------------BOTH------------------------------------*/
namespace logging {

void both_logger::system_log(std::string msg){
    std::cout << colours::reverse_vid << "[" << get_time("%F %T") << "]:PLODD:INTERNAL_SYSTEM:" << msg << colours::reset << "\n";
}

void both_logger::set_level(logging_level new_level){
    logging::console.set_level(new_level);
    logging::file.set_level(new_level);
}

void both_logger::set_name(std::string new_name){
    system_log("\"both\" logger is attempting to change other logger's names to \"" + new_name + "\".");
    logging::console.set_name(new_name);
    logging::file.set_name(new_name);
}

void both_logger::debug(std::string msg){
    logging::console.debug(msg);
    logging::file.debug(msg);
}

void both_logger::info(std::string msg){
    logging::console.info(msg);
    logging::file.info(msg);
}

void both_logger::warn(std::string msg){
    logging::console.warn(msg);
    logging::file.warn(msg);
}

void both_logger::error(std::string msg){
    logging::console.error(msg);
    logging::file.error(msg);
}

both_logger both{};

} //logging