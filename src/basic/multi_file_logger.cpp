//  Copyright (C) Elijah Hopp 2020, No Rights Reserved.
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

namespace {
    _shared_mf_handle * find_or_add_shared_handle(std::string path, std::list<_shared_mf_handle>& handle_list){
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

        //No matching handle was found:
        handle_list.emplace_back(path, 1);
        return &handle_list.back();
    }

    bool remove_dependent(std::string path, std::list<_shared_mf_handle>& handle_list){
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
} //namespace

std::list<_shared_mf_handle> multi_file_logger::shared_file_handle_list = {};

void _shared_mf_handle::init_files(){
    //main.log
    main_file.open(path + "main.log", std::ios::out | std::ios::trunc);
    if(!main_file){
        throw std::runtime_error("Opening of main.log file failed with the path " + path + "main.log" + ".");
    }
    //debug.log
    debug_file.open(path + "debug.log", std::ios::out | std::ios::trunc);
    if(!debug_file){
        throw std::runtime_error("Opening of debug.log file failed with the path " + path + "main.log" + ".");
    }
    //errors.log
    error_file.open(path + "errors.log", std::ios::out | std::ios::trunc);
    if(!error_file){
        throw std::runtime_error("Opening of error.log file failed with the path " + path + "main.log" + ".");
    }
    std::string start_msg = "Starting PLODD logging on " + get_date() + " at " + get_time() + "...\n";
    main_file << start_msg; debug_file << start_msg; error_file << start_msg;
}

multi_file_logger::multi_file_logger(std::string out_dp, std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level){
    //Insure path has a trailing slash:
    out_dp = (out_dp.substr(out_dp.size() - 1, out_dp.size()) == "/") ? out_dp : out_dp + "/";
    //
    shared_file_handles = find_or_add_shared_handle(out_dp, shared_file_handle_list);
    //
    if(!shared_file_handles->main_file.is_open()){
        shared_file_handles->init_files();
    }
}

multi_file_logger::~multi_file_logger(){
    remove_dependent(shared_file_handles->path, shared_file_handle_list);
}

void multi_file_logger::clear_files(){
    //Initing clears the files. 
    shared_file_handles->init_files();
}

void multi_file_logger::debug(std::string msg){
    std::string formatted_log = "[" + get_time() + "]:" + logger_name + ":DEBUG:" + msg;
    if(logger_level == logging_level::DEBUG){
        shared_file_handles->main_file << formatted_log << std::endl;
    }
    shared_file_handles->debug_file << formatted_log << std::endl;
}

void multi_file_logger::info(std::string msg){
    std::string formatted_log = "[" + get_time() + "]:" + logger_name + ":INFO:" + msg;
    if(logger_level <= logging_level::INFO){
        shared_file_handles->main_file << formatted_log << std::endl;
    }
    shared_file_handles->debug_file << formatted_log << std::endl;
}

void multi_file_logger::warn(std::string msg){
    std::string formatted_log = "[" + get_time() + "]:" + logger_name + ":WARN:" + msg;
    if(logger_level <= logging_level::WARN){
        shared_file_handles->main_file << formatted_log << std::endl;
    }
    shared_file_handles->debug_file << formatted_log << std::endl;
}

void multi_file_logger::error(std::string msg){
    std::string formatted_log = "[" + get_time() + "]:" + logger_name + ":ERROR:" + msg;
    shared_file_handles->main_file << formatted_log << std::endl;
    shared_file_handles->debug_file << formatted_log << std::endl;
    shared_file_handles->error_file << formatted_log << std::endl; 
}

} //logging