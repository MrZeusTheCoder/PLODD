//  Copyright (C) Elijah Hopp 2020, All Rights Reserved.
//
//  The implementation file for "PLODD/basic/single_file_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/single_file_logger.h>

#include <PLODD/time.hpp>
//-----------------------------SINGLE-FILE_LOGGER-----------------------------//
namespace pld {

single_file_logger::single_file_logger(std::string path, std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level){
    init_file(path);
}

void single_file_logger::init_file(std::string path){
    
}

void single_file_logger::debug(std::string msg){
    if(logger_level == logging_level::DEBUG){
        out_file << "[" << get_time() << "]:" << logger_name << ":DEBUG:" << msg << std::endl;
    }
}

void single_file_logger::info(std::string msg){
    if(logger_level <= logging_level::INFO){
        out_file << "[" << get_time() << "]:" << logger_name << ":INFO:" << msg << std::endl;
    }
}

void single_file_logger::warn(std::string msg){
    if(logger_level == logging_level::WARN){
        out_file << "[" << get_time() << "]:" << logger_name << ":WARN:" << msg << std::endl;
    }
}

void single_file_logger::error(std::string msg){
    out_file << "[" << get_time() << "]:" << logger_name << ":ERROR:" << msg << std::endl;
}

} //pld