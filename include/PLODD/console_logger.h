//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  This header makes a console logger class, and make an instance of the
//  console logger globally available.
//
//--------------------------------DEFINE_GUARD--------------------------------//
#ifndef PLODD_CONSOLE_LOGGER_H_
#define PLODD_CONSOLE_LOGGER_H_
//----------------------------------INCLUDES----------------------------------//
#include <iostream>

#include <PLODD/base.h>
#include "fmt/format.h"
//-------------------------------CONSOLE_LOGGER-------------------------------//
namespace logging {

class console_logger : public base_logger {
    private:
        void system_log(std::string msg);
    public:
        console_logger(std::string logger_name_, logging_level logging_level_);
        void set_level(logging_level new_level);
        void set_name(std::string new_name);
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
};

extern console_logger console;

} //logging
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_LOGGING_H_