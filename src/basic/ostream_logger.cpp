//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/basic/ostream_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/ostream_logger.h>

#include <PLODD/time.hpp>
//------------------------------OSTREAM_LOGGER--------------------------------//
namespace pld {

ostream_logger::ostream_logger(std::ostream * stream_ptr, std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level), stream_ptr(stream_ptr){}

void ostream_logger::set_stream(std::ostream * new_stream_ptr){
    stream_ptr = new_stream_ptr;
}

void ostream_logger::debug(std::string msg){
    if(logger_level == logging_level::DEBUG){
        #if PLODD_NO_ANSI
            (*stream_ptr) << "[" << get_time() << "]:" << logger_name << ":DEBUG:" << msg << "\n";
        #else
            (*stream_ptr) << colours::gray << "[" << get_time() << "]:" << logger_name << ":DEBUG:" << msg << colours::reset << "\n";
        #endif
    }
}

void ostream_logger::info(std::string msg){
    if(logger_level <= logging_level::INFO){
        #if PLODD_NO_ANSI
            (*stream_ptr) << "[" << get_time() << "]:" << logger_name << ":INFO:" << msg << "\n";
        #else
            (*stream_ptr) << colours::white << "[" << get_time() << "]:" << logger_name << ":INFO:" << msg << colours::reset << "\n";
        #endif
    }
}
void ostream_logger::warn(std::string msg){
    if(logger_level <= logging_level::WARN){
        #if PLODD_NO_ANSI
            (*stream_ptr) << "[" << get_time() << "]:" << logger_name << ":WARN:" << msg << "\n";
        #else
            (*stream_ptr) << colours::yellow << "[" << get_time() << "]:" << logger_name << ":WARN:" << msg << colours::reset << "\n";
        #endif
    }
}
void ostream_logger::error(std::string msg){
    #if PLODD_NO_ANSI
        (*stream_ptr) << "[" << get_time() << "]:" << logger_name << ":ERROR:" << msg << "\n";
    #else
        (*stream_ptr) << colours::red << "[" << get_time() << "]:" << logger_name << ":ERROR:" << msg << colours::reset << "\n";
    #endif
}

} //pld