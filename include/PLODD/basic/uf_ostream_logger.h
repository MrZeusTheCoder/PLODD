#ifndef PLODD_UF_OSTREAM_LOGGER_H_
#define PLODD_UF_OSTREAM_LOGGER_H_
//----------------------------------INCLUDES----------------------------------//
#include "base.h"

#include <string>
#include <ostream>
//-------------------------UNFORMATTED_OSTREAM_LOGGER-------------------------//
namespace pld {

class PLODD_API uf_ostream_logger : public base_logger {
    private:
        std::ostream * stream_ptr;
    public:
        uf_ostream_logger(std::ostream * stream_ptr, std::string logger_name, logging_level logger_level) : base_logger(logger_name, logger_level), stream_ptr(stream_ptr){}
        void set_stream(std::ostream * new_stream_ptr);
        virtual void debug(std::string msg);
        virtual void info(std::string msg);
        virtual void warn(std::string msg);
        virtual void error(std::string msg);
};

} //pld
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_UF_OSTREAM_LOGGER_H_