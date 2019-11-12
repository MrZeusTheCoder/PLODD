//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/base.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/base.h>
//--------------------------------LOGGING_BASE--------------------------------//
namespace logging {
//-------------------------LEVEL_NAME--------------------------//
std::string level_name(logging_level level){
    switch(level){
        default:
            return std::string("ERROR");
        case logging::level::DEBUG:
            return std::string("DEBUG");
        case logging::level::INFO:
            return std::string("INFO");
        case logging::level::WARN:
            return std::string("WARN");
        case logging::level::ERROR:
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

} //logging