/*
///////////////////////////////////////////////////////////////////////
/// @file stream_logger.cpp
/// @author Elijah Hopp (github.mrzeusthecoder@gmail.com)
/// @brief stream_logger.h implementation file
/// @version 0.1
/// @date 2019-07-22
/// 
/// @copyright Copyright (c) 2019 Elijah Hopp, No Rights Reserved
///
/// @see stream_logger.h
/// 
//////////////////////////////////////////////////////////////////////
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/flexy_logger.h>

#include <iostream>

#include <PLODD/get_time.hpp>
//-------------------------------STREAM_LOGGER--------------------------------//
namespace logging {



template<typename T>
void stream_logger<T, false>::debug(std::string msg){
    if(logger_level == logging_level::DEBUG){
        (*stream_ptr) << msg << "\n";
    }
}
template<typename T>
void stream_logger<T, false>::info(std::string msg){
    if(logger_level <= logging_level::INFO){
        (*stream_ptr) << msg << "\n";
    }
}
template<typename T>
void stream_logger<T, false>::warn(std::string msg){
    if(logger_level <= logging_level::WARN){
        (*stream_ptr) << msg << "\n";
    }
}
template<typename T>
void stream_logger<T, false>::error(std::string msg){
    (*stream_ptr) << msg << "\n";
}


template<typename T>
void stream_logger<T, true>::debug(std::string msg){
    if(logger_level == logging_level::DEBUG){
        #ifdef PLODD_NO_ANSI
            (*stream_ptr) << "[" << get_time("%T") << "]:" << logger_name << ":DEBUG:" << msg << "\n";
        #else
            std::cout << colours::gray << "[" << get_time("%T") << "]:" << logger_name << ":DEBUG:" << msg << colours::reset << "\n";
        #endif
    }
}

template<typename T>
void stream_logger<T, true>::info(std::string msg){
    if(logger_level <= logging_level::INFO){
        #ifdef PLODD_NO_ANSI
            (*stream_ptr) << "[" << get_time("%T") << "]:" << logger_name << ":INFO:" << msg << "\n";
        #else
            (*stream_ptr) << colours::white << "[" << get_time("%T") << "]:" << logger_name << ":INFO:" << msg << colours::reset << "\n";
        #endif
    }
}

template<typename T>
void stream_logger<T, true>::warn(std::string msg){
    if(logger_level == logging_level::DEBUG){
        #ifdef PLODD_NO_ANSI
            (*stream_ptr) << "[" << get_time("%T") << "]:" << logger_name << ":WARN:" << msg << "\n";
        #else
            (*stream_ptr) << colours::yellow << "[" << get_time("%T") << "]:" << logger_name << ":WARN:" << msg << colours::reset << "\n";
        #endif
    }
}

template<typename T>
void stream_logger<T, true>::error(std::string msg){
    #ifdef PLODD_NO_ANSI
        (*stream_ptr) << "[" << get_time("%T") << "]:" << logger_name << ":ERROR:" << msg << "\n";
    #else
        (*stream_ptr) << colours::red << "[" << get_time("%T") << "]:" << logger_name << ":ERROR:" << msg << colours::reset << "\n";
    #endif
}


} //logging
*/