//  Copyright (C) Elijah Hopp 2020, No Rights Reserved.
//
//  The file logger header file.
//
//--------------------------------DEFINE_GUARD--------------------------------//
#ifndef PLODD_FILE_LOGGER_H_
#define PLODD_FILE_LOGGER_H_
//----------------------------------INCLUDES----------------------------------//
#include <functional>

#include "multi_file_logger.h"
//--------------------------------FILE_LOGGER---------------------------------//
namespace pld {

//A quick, ignoreable class declaration:
class _mf_logger_singleton : public base_logger {
    private:
        static multi_file_logger * mf_logger_obj;
        //These switch to the multi-file logger when it has been constructed. 
        //Having function pointers increases speed over an if statement.
        static std::function<void(std::string)> debug_function;
        static std::function<void(std::string)> info_function;
        static std::function<void(std::string)> warn_function;
        static std::function<void(std::string)> error_function;
    public:
        _mf_logger_singleton();


        _mf_logger_singleton(const _mf_logger_singleton &) = delete;
        _mf_logger_singleton& operator=(const _mf_logger_singleton &) = delete;

        void init_files(std::string path);
        void clear_files();

        std::string get_name();
        void set_name(std::string new_name);

        logging_level get_level();
        void set_level(logging_level new_level);

        void debug(std::string msg){ debug_function(msg); }
        void info(std::string msg){ info_function(msg); }
        void warn(std::string msg){ warn_function(msg); }
        void error(std::string msg){ error_function(msg); }
};

////////////////////////////////////////////////////////////////////////////////
/// @brief The internal file PLODD file logger.
/// 
////////////////////////////////////////////////////////////////////////////////
extern PLODD_API _mf_logger_singleton file;

} //pld
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_FILE_LOGGER_H_