//  Copyright (C) Elijah Hopp 2020, All Rights Reserved.
//
//  The implementation file for "PLODD/basic/single_file_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/single_file_logger.h>

#include <PLODD/basic/time.hpp>
//-----------------------------SINGLE-FILE_LOGGER-----------------------------//
namespace pld {

single_file_logger::single_file_logger(std::string path, std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level){
    init_file(path);
}

single_file_logger::single_file_logger(std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level){}

void single_file_logger::init_file(std::string path){
    output_file.open(path, std::ios::out | std::ios::trunc);
    if(!output_file){
        throw std::runtime_error("Error opening a file for a PLODD single_file_logger named " + logger_name + " under the path \"" + path + "\".");
    }
    output_file << "Started a PLODD single file logger in this file on " << get_date() << " at " << get_time() << "..." << std::endl;
}

void single_file_logger::debug(std::string msg){
    if(logger_level == logging_level::DEBUG){
        output_file << "[" << get_time() << "]:" << logger_name << ":DEBUG:" << msg << std::endl;
    }
}

void single_file_logger::info(std::string msg){
    if(logger_level <= logging_level::INFO){
        output_file << "[" << get_time() << "]:" << logger_name << ":INFO:" << msg << std::endl;
    }
}

void single_file_logger::warn(std::string msg){
    if(logger_level <= logging_level::WARN){
        output_file << "[" << get_time() << "]:" << logger_name << ":WARN:" << msg << std::endl;
    }
}

void single_file_logger::error(std::string msg){
    output_file << "[" << get_time() << "]:" << logger_name << ":ERROR:" << msg << std::endl;
}

} //pld