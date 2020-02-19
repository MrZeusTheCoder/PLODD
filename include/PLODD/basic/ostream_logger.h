//////////////////////////////////////////////////////////////////////
/// @file ostream_logger.h
/// @author Elijah Hopp (github.mrzeusthecoder@gmail.com)
/// @brief 
/// @version 0.1
/// @date 2019-11-12
/// 
/// @copyright Copyright (c) 2019 Elijah Hopp, No Rights Reserved
/// 
//////////////////////////////////////////////////////////////////////
#ifndef PLODD_OSTREAM_LOGGER_H_
#define PLODD_OSTREAM_LOGGER_H_
//----------------------------------INCLUDES----------------------------------//
#include "base.h"

#include <string>
#include <ostream>
//-------------------------------OSTREAM_LOGGER-------------------------------//
namespace pld {

class ostream_logger : public base_logger {
    private:
        std::ostream * stream_ptr;
    public:
        ostream_logger(std::ostream * stream_ptr, std::string logger_name, logging_level logger_level);
        void set_stream(std::ostream * new_stream_ptr);
        virtual void debug(std::string msg);
        virtual void info(std::string msg);
        virtual void warn(std::string msg);
        virtual void error(std::string msg);
};

} //pld
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_OSTREAM_LOGGER_H_