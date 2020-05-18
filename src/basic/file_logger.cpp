//  Copyright (C) Elijah Hopp 2020, No Rights Reserved.
//
//  The implementation file for "PLODD/basic/file_logger.h"
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/file_logger.h>

#include <PLODD/basic/base.h>
#include <PLODD/basic/multi_file_logger.h>
//--------------------------------FILE_LOGGER---------------------------------//
namespace pld {

_mf_logger_singleton file{};

multi_file_logger * _mf_logger_singleton::mf_logger_obj = nullptr;

std::function<void(std::string)> _mf_logger_singleton::debug_function = [](std::string msg){ (void)(msg); }; //(void)(msg) makes the compiler ingore them for unused param warnings.
std::function<void(std::string)> _mf_logger_singleton::info_function = [](std::string msg){ (void)(msg); };
std::function<void(std::string)> _mf_logger_singleton::warn_function = [](std::string msg){ (void)(msg); };
std::function<void(std::string)> _mf_logger_singleton::error_function = [](std::string msg){ (void)(msg); };

_mf_logger_singleton::_mf_logger_singleton() : base_logger("FILE", level::DEBUG){}

void _mf_logger_singleton::init_files(std::string path){
    if(mf_logger_obj == nullptr){
        mf_logger_obj = new multi_file_logger{path, logger_name, logger_level};
    } else {
        delete mf_logger_obj;
        mf_logger_obj = new multi_file_logger{path, logger_name, logger_level};
    }
    debug_function = [](std::string msg){ mf_logger_obj->debug(msg); };
    info_function = [](std::string msg){ mf_logger_obj->info(msg); };
    warn_function = [](std::string msg){ mf_logger_obj->warn(msg); };
    error_function = [](std::string msg){ mf_logger_obj->error(msg); };
}

std::string _mf_logger_singleton::get_name(){
    return logger_name;
}

void _mf_logger_singleton::set_name(std::string new_name){
    logger_name = new_name;
    if(mf_logger_obj != nullptr){
        mf_logger_obj->set_name(logger_name);
    }
}

logging_level _mf_logger_singleton::get_level(){
    return logger_level;
}

void _mf_logger_singleton::set_level(logging_level new_level){
    logger_level = new_level;
    if(mf_logger_obj != nullptr){
        mf_logger_obj->set_level(logger_level);
    }
}

} //logging