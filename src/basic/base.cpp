//  Copyright (C) Elijah Hopp 2020, No Rights Reserved.
//
//  The implementation file for "PLODD/basic/base.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/base.h>
//--------------------------------LOGGING_BASE--------------------------------//
namespace pld {
//-------------------------LEVEL_NAME--------------------------//
std::string level_name(logging_level passed_level){
    switch(passed_level){
        default:
            return std::string("ERROR");
        case level::DEBUG:
            return std::string("DEBUG");
        case level::INFO:
            return std::string("INFO");
        case level::WARN:
            return std::string("WARN");
        case level::ERROR:
            return std::string("ERROR");
    }
}
//-------------------------BASE_LOGGER-------------------------//
void base_logger::set_level(logging_level new_level){
    logger_level = new_level;
}

void base_logger::set_name(std::string new_name){
    logger_name = new_name;
}

logging_level base_logger::get_level(){
    return logger_level;
}

std::string base_logger::get_name(){
    return logger_name;
}

} //logging