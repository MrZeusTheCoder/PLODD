//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/multi_file_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/multi_file_logger.h>

#include <string>
#include <fstream>

#include <PLODD/base.h>
#include <PLODD/get_time.h>
//-----------------------------MULTI-FILE_LOGGER------------------------------//
namespace logging {

void multi_file_logger::system_log(std::string msg){
    system_log_to_files(msg);
}

void multi_file_logger::system_log_to_files(std::string msg){
    std::string formatted_log = "[" + get_time("%F %T") + "]:PLODD:SYSTEM:" + msg + "\n";
    main_file << formatted_log << std::endl;
    debug_file << formatted_log << std::endl;
    error_file << formatted_log << std::endl;
}

multi_file_logger::multi_file_logger(std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level){}

void multi_file_logger::init_files(std::string explicit_path){
    //main.log
    main_file.open(explicit_path + "main.log", std::ios::out | std::ios::trunc);
    if(!main_file){
        throw std::runtime_error("Opening of main.log file failed.");
    }
    //debug.log
    debug_file.open(explicit_path + "debug.log", std::ios::out | std::ios::trunc);
    if(!debug_file){
        throw std::runtime_error("Opening of debug.log file failed.");
    }
    //errors.log
    error_file.open(explicit_path + "errors.log", std::ios::out | std::ios::trunc);
    if(!error_file){
        throw std::runtime_error("Opening of error.log file failed.");
    }
    std::string start_msg = "Starting PLODD on " + get_time("%D") + " at " + get_time("%T") + "...\n";
    main_file << start_msg; debug_file << start_msg; error_file << start_msg;
}

void multi_file_logger::init_files(){
    debug_file.open("./debug.log", std::ios::out | std::ios::trunc);
    if(!debug_file){
        throw std::runtime_error("Opening of debug.log file failed.");
    }
    error_file.open("./errors.log", std::ios::out | std::ios::app);
    if(!error_file){
        throw std::runtime_error("Opening of error.log file failed.");
    }
    main_file.open("./main.log", std::ios::out | std::ios::trunc);
    if(!main_file){
        throw std::runtime_error("Opening of main.log file failed.");
    }
    error_file << "\n\nStarting PLODD on " << get_time("%c") << "...\n";
}

void multi_file_logger::set_level(logging_level new_level){
    logger_level = new_level;
}

void multi_file_logger::set_name(std::string new_name){
    logger_name = new_name;
}

void multi_file_logger::debug(std::string msg){
    std::string formatted_log = "[" + get_time("%F %T") + "]:" + logger_name + ":DEBUG:" + msg;
    if(logger_level == logging_level::DEBUG){
        main_file << formatted_log << std::endl;
    }
    debug_file << formatted_log << std::endl;
}

void multi_file_logger::info(std::string msg){
    std::string formatted_log = "[" + get_time("%F %T") + "]:" + logger_name + ":INFO:" + msg;
    if(logger_level <= logging_level::INFO){
        main_file << formatted_log << std::endl;
    }
    debug_file << formatted_log << std::endl;
}

void multi_file_logger::warn(std::string msg){
    std::string formatted_log = "[" + get_time("%F %T") + "]:" + logger_name + ":WARN:" + msg;
    if(logger_level <= logging_level::WARN){
        main_file << formatted_log << std::endl;
    }
    debug_file << formatted_log << std::endl;
}

void multi_file_logger::error(std::string msg){
    std::string formatted_log = "[" + get_time("%F %T") + "]:" + logger_name + ":ERROR:" + msg;
    main_file << formatted_log << std::endl;
    debug_file << formatted_log << std::endl;
    error_file << formatted_log << std::endl; 
}

} //logging