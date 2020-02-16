//  Copyright (C) Elijah Hopp 2020, All Rights Reserved.
//
//  The implementation file for "PLODD/basic/uf_ostream_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/uf_ostream_logger.h>
//-------------------------UNFORMATTED_OSTREAM_LOGGER-------------------------//
namespace pld {

void uf_ostream_logger::set_stream(std::ostream * new_stream_ptr){
    stream_ptr = new_stream_ptr;
}

void uf_ostream_logger::debug(std::string msg){
    if(logger_level == logging_level::DEBUG){
        (*stream_ptr) << msg;
    }
}

void uf_ostream_logger::info(std::string msg){
    if(logger_level <= logging_level::INFO){
        (*stream_ptr) << msg;
    }
}
void uf_ostream_logger::warn(std::string msg){
    if(logger_level <= logging_level::WARN){
        (*stream_ptr) << msg;
    }
}
void uf_ostream_logger::error(std::string msg){
    (*stream_ptr) << msg;
}

} //pld