//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  A class that allows you to log to both the console and the files.
// 
/*--------------------------------DEFINE_GUARD--------------------------------*/
#ifndef PLODD_BOTH_H_
#define PLODD_BOTH_H_
/*----------------------------------INCLUDES----------------------------------*/
#include <PLODD/base.h>

#include <string>

#include <PLODD/console_logger.h>
#include <PLODD/file_logger.h>
/*------------------------------------BOTH------------------------------------*/
namespace logging {

class both_logger : public base_logger {
    private:
        void system_log(std::string msg);
    public:
        both_logger() : base_logger("BOTH", logging_level::ERROR){};
        void set_level(logging_level new_level);
        void set_name(std::string new_name);
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
};

extern both_logger both;

} //logging
/*-----------------------------------END_IF-----------------------------------*/
#endif //PLODD_BOTH_H_