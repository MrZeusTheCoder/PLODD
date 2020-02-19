//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/basic/both.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/both.h>

#include <PLODD/basic/base.h>
#include <PLODD/basic/console_logger.h>
#include <PLODD/basic/file_logger.h>
#include <PLODD/time.hpp>
//------------------------------------BOTH------------------------------------//
namespace pld {

void both_logger::set_level(logging_level new_level){
    console.set_level(new_level);
    file.set_level(new_level);
}

void both_logger::set_name(std::string new_name){
    console.set_name(new_name);
    file.set_name(new_name);
}

void both_logger::debug(std::string msg){
    console.debug(msg);
    file.debug(msg);
}

void both_logger::info(std::string msg){
    console.info(msg);
    file.info(msg);
}

void both_logger::warn(std::string msg){
    console.warn(msg);
    file.warn(msg);
}

void both_logger::error(std::string msg){
    console.error(msg);
    file.error(msg);
}

both_logger both{};

} //logging