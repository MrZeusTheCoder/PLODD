//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/ostream_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/ostream_logger.h>

#include <PLODD/get_time.h>
//-------------------------------OSTREAM_LOGGER-------------------------------//
namespace logging {

void unformatted_ostream_logger::debug(std::string msg){
    if(logger_level == logging_level::DEBUG){
        (*stream_ptr) << msg;
    }
}

void unformatted_ostream_logger::info(std::string msg){
    if(logger_level <= logging_level::INFO){
        (*stream_ptr) << msg;
    }
}
void unformatted_ostream_logger::warn(std::string msg){
    if(logger_level <= logging_level::WARN){
        (*stream_ptr) << msg;
    }
}
void unformatted_ostream_logger::error(std::string msg){
    (*stream_ptr) << msg;
}

void ostream_logger::debug(std::string msg){
    if(logger_level == logging_level::DEBUG){
        #if NO_ANSI_PLODD
            (*stream_ptr) << "[" << get_time("%T") << "]:" << logger_name << ":DEBUG:" << msg << "\n";
        #else
            (*stream_ptr) << colours::gray << "[" << get_time("%T") << "]:" << logger_name << ":DEBUG:" << msg << colours::reset << "\n";
        #endif
    }
}

void ostream_logger::info(std::string msg){
    if(logger_level <= logging_level::INFO){
        #if NO_ANSI_PLODD
            (*stream_ptr) << "[" << get_time("%T") << "]:" << logger_name << ":INFO:" << msg << "\n";
        #else
            (*stream_ptr) << colours::white << "[" << get_time("%T") << "]:" << logger_name << ":INFO:" << msg << colours::reset << "\n";
        #endif
    }
}
void ostream_logger::warn(std::string msg){
    if(logger_level <= logging_level::WARN){
        #if NO_ANSI_PLODD
            (*stream_ptr) << "[" << get_time("%T") << "]:" << logger_name << ":WARN:" << msg << "\n";
        #else
            (*stream_ptr) << colours::yellow << "[" << get_time("%T") << "]:" << logger_name << ":WARN:" << msg << colours::reset << "\n";
        #endif
    }
}
void ostream_logger::error(std::string msg){
    #if NO_ANSI_PLODD
        (*stream_ptr) << "[" << get_time("%T") << "]:" << logger_name << ":ERROR:" << msg << "\n";
    #else
        (*stream_ptr) << colours::red << "[" << get_time("%T") << "]:" << logger_name << ":ERROR:" << msg << colours::reset << "\n";
    #endif
}

} //logging