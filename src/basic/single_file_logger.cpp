//  Copyright (C) Elijah Hopp 2020, All Rights Reserved.
//
//  The implementation file for "PLODD/basic/single_file_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/single_file_logger.h>

#include <PLODD/basic/time.hpp>
//-----------------------------SINGLE-FILE_LOGGER-----------------------------//
namespace pld {

namespace {
    _shared_file_handle * find_or_add_shared_handle(std::string path, std::list<_shared_file_handle>& handle_list){
        if(handle_list.begin() == handle_list.end()){
            handle_list.emplace_back(path, 1);
            return &handle_list.back();
        }

        for(auto& it : handle_list){
            if(it.path == path){
                it.dependents++;
                return &it;
            } else {
                continue;
            }
        }

        //No matches:
        handle_list.emplace_back(path, 1);
        return &handle_list.back();
    }

    bool remove_dependent(std::string path, std::list<_shared_file_handle>& handle_list){
        if(handle_list.begin() == handle_list.end()){
            return false;
        }

        for(auto it = handle_list.begin(); it != handle_list.end(); it++){
            if(it->path == path){
                if(it->dependents <= 1){
                    //We're the last dependent!
                    handle_list.erase(it);
                    return true;
                } else {
                    it->dependents--;
                    return false;
                }
            } else {
                continue;
            }
        }

        return false;
    }
}

std::list<_shared_file_handle> single_file_logger::shared_file_handle_list = {};

void _shared_file_handle::init_file(){
    file.open(path, std::ios::out | std::ios::trunc);
    if(!file){
        throw std::runtime_error("Opening of log file failed with the path " + path + ".");
    } else {
        file << "Starting PLODD logging on " << get_date() << " at " << get_time() << "...\n";
    }
}

single_file_logger::single_file_logger(std::string path, std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level){
    shared_handle = find_or_add_shared_handle(path, shared_file_handle_list);
    //
    if(!shared_handle->file.is_open()){
        shared_handle->init_file();
    }
}

single_file_logger::~single_file_logger(){
    remove_dependent(shared_handle->path, shared_file_handle_list);
}

void single_file_logger::debug(std::string msg){
    if(logger_level == logging_level::DEBUG){
        shared_handle->file << "[" << get_time() << "]:" << logger_name << ":DEBUG:" << msg << std::endl;
    }
}

void single_file_logger::info(std::string msg){
    if(logger_level <= logging_level::INFO){
        shared_handle->file << "[" << get_time() << "]:" << logger_name << ":INFO:" << msg << std::endl;
    }
}

void single_file_logger::warn(std::string msg){
    if(logger_level <= logging_level::WARN){
        shared_handle->file << "[" << get_time() << "]:" << logger_name << ":WARN:" << msg << std::endl;
    }
}

void single_file_logger::error(std::string msg){
    shared_handle->file << "[" << get_time() << "]:" << logger_name << ":ERROR:" << msg << std::endl;
}

} //pld