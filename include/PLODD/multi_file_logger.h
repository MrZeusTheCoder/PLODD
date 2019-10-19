//////////////////////////////////////////////////////////////////////
/// @file multi_file_logger.h
/// @author Elijah Hopp (github.mrzeusthecoder@gmail.com)
/// @brief A logger that outputs to multipule files.
/// @version 0.1
/// @date 2019-07-22 
///
/// @copyright Copyright (c) 2019 Elijah Hopp, No Rights Reserved
/// 
//////////////////////////////////////////////////////////////////////
/*--------------------------------DEFINE_GUARD--------------------------------*/
#ifndef PLODD_MULTI_FILE_LOGGER_H_
#define PLODD_MULTI_FILE_LOGGER_H_
/*----------------------------------INCLUDES----------------------------------*/
#include <fstream>
#include <string>

#include <PLODD/base.h>
/*-----------------------------MULTI-FILE_LOGGER------------------------------*/
namespace logging {

//////////////////////////////////////////////////////////////////////
/// @brief A multi-file(-sink?) file logger that logs to three 
/// files.
/// 
/// A multi-sink file logger that outputs into three files:
/// "debug.log", "main.log", and "errors.log". "debug.log" is
/// written all logs no matter the logging level that is set on a
/// per-logger basis. "main.log" is only written all the logs of
/// equal or greater logging level. i.e. only WARNING and ERROR if
/// the level is set to WARNING and not INFO and DEBUG.
/// "errors.log" is only written logs that are of the ERROR
/// logging level.
///
//////////////////////////////////////////////////////////////////////
class multi_file_logger : public base_logger {
    private:
        std::ofstream main_file;
        std::ofstream debug_file;
        std::ofstream error_file;
        void system_log(std::string msg);
        void system_log_to_files(std::string msg);
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief Construct a new multi-file logger object
        /// 
        /// @param logger_name_ The name used in the format.
        /// @param logger_level_ The level that the 
        //////////////////////////////////////////////////////////////////////
        multi_file_logger(std::string logger_name_, logging_level logger_level_);
        //////////////////////////////////////////////////////////////////////
        /// @brief Initialize/clears (re-inits) log files in the CWD.
        //////////////////////////////////////////////////////////////////////
        void init_files();
        //////////////////////////////////////////////////////////////////////
        /// @brief Initialize/clears (re-inits) log files in the explicit path.
        /// 
        /// @param explicit_path Full or relative path to the logging 
        /// location.
        //////////////////////////////////////////////////////////////////////
        void init_files(std::string explicit_path);
        void set_level(logging_level new_level);
        void set_name(std::string new_name);
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
};

} //logging
/*-----------------------------------END_IF-----------------------------------*/
#endif //PLODD_MULTI_FILE_LOGGER_H_