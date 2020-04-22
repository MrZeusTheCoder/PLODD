//  Copyright (C) Elijah Hopp 2020, No Rights Reserved.
//
//  A class that allows you to log to both the console and the files.
// 
//--------------------------------DEFINE_GUARD--------------------------------//
#ifndef PLODD_BOTH_H_
#define PLODD_BOTH_H_
//----------------------------------INCLUDES----------------------------------//
#include "base.h"

#include <string>
//------------------------------------BOTH------------------------------------//
namespace pld {

class PLODD_API both_logger : public base_logger {
    public:
        both_logger() : base_logger("BOTH", logging_level::ERROR){};
        void set_level(logging_level new_level);
        void set_name(std::string new_name);
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
};

extern PLODD_API both_logger both;

} //pld
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_BOTH_H_