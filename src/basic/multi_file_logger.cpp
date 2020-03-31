//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/basic/multi_file_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/multi_file_logger.h>

#include <string>
#include <fstream>

#include <PLODD/basic/base.h>
#include <PLODD/basic/time.hpp>
//-----------------------------MULTI-FILE_LOGGER------------------------------//
namespace pld {

multi_file_logger::multi_file_logger(std::string output_directory_path, std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level){
    try {
        init_files(output_directory_path);
    } catch(std::exception& init_error) {
        throw std::runtime_error("Failed to construct an instance of a PLODD multi_file_logger named " + logger_name + " because it was unable to open files under the path, \"" + output_directory_path + "\".\nUpstream error is:" + init_error.what());
    }
}

multi_file_logger::multi_file_logger(std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level){}

void multi_file_logger::init_files(std::string path){
    //Insure path has a trailing slash:
    path = (path.substr(path.size() - 1, path.size()) == "/") ? path : path + "/";
    //main.log
    main_file.open(path + "main.log", std::ios::out | std::ios::trunc);
    if(!main_file){
        throw std::runtime_error("Opening of main.log file failed for a logger named " + logger_name + " with the path " + path + "main.log" + ".");
    }
    //debug.log
    debug_file.open(path + "debug.log", std::ios::out | std::ios::trunc);
    if(!debug_file){
        throw std::runtime_error("Opening of debug.log file failed for a logger named " + logger_name + " with the path " + path + "main.log" + ".");
    }
    //errors.log
    error_file.open(path + "errors.log", std::ios::out | std::ios::trunc);
    if(!error_file){
        throw std::runtime_error("Opening of error.log file failed for a logger named " + logger_name + " with the path " + path + "main.log" + ".");
    }
    std::string start_msg = "Starting PLODD on " + get_date() + " at " + get_time() + "...\n";
    main_file << start_msg; debug_file << start_msg; error_file << start_msg;
}

void multi_file_logger::debug(std::string msg){
    std::string formatted_log = "[" + get_time() + "]:" + logger_name + ":DEBUG:" + msg;
    if(logger_level == logging_level::DEBUG){
        main_file << formatted_log << std::endl;
    }
    debug_file << formatted_log << std::endl;
}

void multi_file_logger::info(std::string msg){
    std::string formatted_log = "[" + get_time() + "]:" + logger_name + ":INFO:" + msg;
    if(logger_level <= logging_level::INFO){
        main_file << formatted_log << std::endl;
    }
    debug_file << formatted_log << std::endl;
}

void multi_file_logger::warn(std::string msg){
    std::string formatted_log = "[" + get_time() + "]:" + logger_name + ":WARN:" + msg;
    if(logger_level <= logging_level::WARN){
        main_file << formatted_log << std::endl;
    }
    debug_file << formatted_log << std::endl;
}

void multi_file_logger::error(std::string msg){
    std::string formatted_log = "[" + get_time() + "]:" + logger_name + ":ERROR:" + msg;
    main_file << formatted_log << std::endl;
    debug_file << formatted_log << std::endl;
    error_file << formatted_log << std::endl; 
}

} //logging