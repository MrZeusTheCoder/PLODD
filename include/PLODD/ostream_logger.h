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
#include <PLODD/base.h>

#include <string>
#include <ostream>
//-------------------------------OSTREAM_LOGGER-------------------------------//
namespace logging {
//You're welcome to inherit from this one:
class ostream_logger : public base_logger {
    private:
        std::ostream * stream_ptr;
    public:
        ostream_logger(std::ostream * stream_ptr, std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level), stream_ptr(stream_ptr){}
        virtual void debug(std::string msg);
        virtual void info(std::string msg);
        virtual void warn(std::string msg);
        virtual void error(std::string msg);
};
//, but not this one:
class unformatted_ostream_logger : public base_logger {
    private:
        std::ostream * stream_ptr;
    public:
        unformatted_ostream_logger(std::ostream * stream_ptr, std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level), stream_ptr(stream_ptr){}
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
};
} //logging
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_OSTREAM_LOGGER_H_