/*
//////////////////////////////////////////////////////////////////////
/// @file stream_logger.h
/// @author Elijah Hopp (github.mrzeusthecoder@gmail.com)
/// @brief 
/// @version 0.1
/// @date 2019-07-22
/// 
/// @copyright Copyright (c) 2019 Elijah Hopp, No Rights Reserved
/// 
//////////////////////////////////////////////////////////////////////
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/base.h>

#include <iostream>
//-------------------------------STREAM_LOGGER--------------------------------//
namespace logging {

template <typename T, bool pretty_print = true>
class stream_logger : public base_logger {
    private:
        T * stream_ptr;
        void system_log(std::string msg);
        stream_logger();
    public:
        stream_logger(T * stream_ptr, std::string name, logging_level level) : 
            stream_ptr(stream_ptr), base_logger(name, level){}
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
};

template <typename T>
class stream_logger<T, false> : public base_logger {
    private:
        T * stream_ptr;
        void system_log(std::string msg);
        stream_logger();
    public:
        stream_logger(T * stream_ptr, std::string name, logging_level level) : 
            stream_ptr(stream_ptr), base_logger(name, level){};
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
};

template <typename T>
class stream_logger<T, true> : public base_logger {
    private:
        T * stream_ptr;
        void system_log(std::string msg);
        stream_logger();
    public:
         stream_logger(T * stream_ptr, std::string name, logging_level level) : 
            stream_ptr(stream_ptr), base_logger(name, level){}
        void debug(std::string msg);
        void info(std::string msg);
        void warn(std::string msg);
        void error(std::string msg);
};

template class stream_logger<std::ostream, true>;
template class stream_logger<std::ostream, false>;

} //logging
*/