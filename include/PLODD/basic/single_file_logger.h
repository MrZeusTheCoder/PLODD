//  Copyright (C) Elijah Hopp 2020, No Rights Reserved.
//--------------------------------DEFINE_GUARD--------------------------------//
#ifndef PLODD_SINGLE_FILE_LOGGER_H_
#define PLODD_SINGLE_FILE_LOGGER_H_
//----------------------------------INCLUDES----------------------------------//
#include "base.h"

#include <fstream>
#include <string>
//-----------------------------SINGLE-FILE_LOGGER-----------------------------//
namespace pld {

class single_file_logger : public base_logger {
    protected:
        std::ofstream output_file;
    public:
        single_file_logger(std::string output_path, std::string logger_name, logging_level logger_level);
        single_file_logger(std::string logger_name, logging_level logger_level);
        void init_file(std::string output_path);
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
};

} //pld
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_SINGLE_FILE_LOGGER_H_