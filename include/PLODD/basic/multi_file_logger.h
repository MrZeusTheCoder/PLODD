//////////////////////////////////////////////////////////////////////
/// @file multi_file_logger.h
/// @author Elijah Hopp (github.mrzeusthecoder@gmail.com)
/// @brief A logger that outputs to multipule files.
/// @version 0.0.0
/// @date 2020-02-24
/// 
/// @copyright Copyright (c) 2020 Elijah Hopp, No Rights Reserved
/// 
//////////////////////////////////////////////////////////////////////
//--------------------------------DEFINE_GUARD--------------------------------//
#ifndef PLODD_MULTI_FILE_LOGGER_H_
#define PLODD_MULTI_FILE_LOGGER_H_
//----------------------------------INCLUDES----------------------------------//
#include "base.h"

#include <fstream>
#include <list>
#include <string>

#include "single_file_logger.h"
//-----------------------------MULTI-FILE_LOGGER------------------------------//
namespace pld {

class _shared_mf_handle {
    public:
        std::string path;
        std::ofstream main_file;
        std::ofstream debug_file;
        std::ofstream error_file;
        uint8_t dependents;
        //
        void init_files();
        //
        _shared_mf_handle() = delete;
        _shared_mf_handle(std::string path, uint8_t dependents) : path(path), dependents(dependents){}
};

//////////////////////////////////////////////////////////////////////
/// @brief A multi-file file logger that logs to three 
/// files.
/// @details A multi-sink file logger that outputs into three files:
/// `debug.log`, `main.log`, and `errors.log`. `debug.log` is
/// written all logs no matter the logging level that is set on a
/// per-logger basis. `main.log` is only written all the logs of
/// equal or greater logging level. i.e. only `WARNING` and `ERROR` if
/// the level is set to `WARNING` and not `INFO` and `DEBUG`.
/// `errors.log` is only written logs that are of the `ERROR`
/// logging level.
///
//////////////////////////////////////////////////////////////////////
class PLODD_API multi_file_logger : public base_logger {
    private:
        //Static list of file handles:
        static std::list<_shared_mf_handle> shared_file_handle_list;
        //
        _shared_mf_handle * shared_file_handles;
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief Constructs a new multi-file logger object and initializes the output files.
        /// @param output_directory_path The path to the directory where the output files are placed
        /// @param logger_name The name of the logger.
        /// @param logger_level The minimum logging level at which the logger will write output.
        //////////////////////////////////////////////////////////////////////
        multi_file_logger(std::string output_directory_path, std::string logger_name, logging_level logger_level);
        ~multi_file_logger();
        
        void clear_files();

        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
};

} //pld
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_MULTI_FILE_LOGGER_H_