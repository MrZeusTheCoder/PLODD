//  Copyright (C) Elijah Hopp 2020, No Rights Reserved.
//--------------------------------DEFINE_GUARD--------------------------------//
#ifndef PLODD_SINGLE_FILE_LOGGER_H_
#define PLODD_SINGLE_FILE_LOGGER_H_
//----------------------------------INCLUDES----------------------------------//
#include "base.h"

#include <fstream>
#include <list>
#include <string>
//-----------------------------SINGLE-FILE_LOGGER-----------------------------//
namespace pld {

class _shared_file_handle {
    public:
        std::string path;
        std::ofstream file;
        uint8_t dependents;
        //
        void init_file();
        //
        _shared_file_handle() = delete;
        _shared_file_handle(std::string path, uint8_t dependents) : path(path), dependents(dependents){}
};

class PLODD_API single_file_logger : public base_logger {
    private:
        static std::list<_shared_file_handle> shared_file_handle_list;
        //
        _shared_file_handle * shared_handle;
    public:
        single_file_logger(std::string output_path, std::string logger_name, logging_level logger_level);
        ~single_file_logger();
        void clear_file();
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
};

} //pld
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_SINGLE_FILE_LOGGER_H_