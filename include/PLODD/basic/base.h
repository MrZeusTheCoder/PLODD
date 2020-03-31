//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  This file provides the needed base needs for any loggers.
// 
//--------------------------------DEFINE_GUARD--------------------------------//
#ifndef PLODD_BASE_H_
#define PLODD_BASE_H_
//----------------------------------INCLUDES----------------------------------//
#include <iostream>
#include "../../fmt/format.h"
//----------------------------DEFINES_AND_STUFFING----------------------------//
#ifdef _WIN32
    #undef ERROR //Windows employee: "Why? Why not? Also, I took an online test that said I was a sadist, but that's unimportant."
    //^^^^^^^^^^ This will undefine any use of the word ERROR. This word is used throughout PLODD. :(
    #define NOMINMAX 1 //I like the "1". Feels more explicit.
    #define PLODD_NO_ANSI 1
#endif

//PLODD_API for shared libs.
#ifndef PLODD_STATIC
    #ifdef _WIN32
        #ifdef PLODD_EXPORT_API
            #define PLODD_API __declspec(dllexport)
        #else
            #define PLODD_API __declspec(dllimport)
        #endif

        #ifdef _MSC_VER
            #pragma warning(disable: 4251)
        #endif
    #else
        #define PLODD_API 
    #endif
#else
    #define PLODD_API 
#endif

//---------------------------------PLODD_BASE---------------------------------//
namespace pld {

namespace colours {
//Notice how most of these are bold. I wanted them most of them to be bold, 
//but didn't want to write white_bold and red_bold all the time. It isn't 
//laziness, it's... abstraction? :D
const std::string reset =  "\033[0m";
const std::string gray = "\033[0;37m";
const std::string white = "\033[1;37m";
const std::string yellow = "\033[1;33m";
const std::string red = "\033[1;31m";
const std::string reverse_vid = "\033[7m";
} //colours

//////////////////////////////////////////////////////////////////////
/// @brief The logging levels that define the volume at which you want to yell things.
//////////////////////////////////////////////////////////////////////
enum class PLODD_API level {
    DEBUG, //No one need that, right?
    INFO, //Helpful.
    WARN, //Calm down, it'll be fine.
    ERROR, //Oh no, he has broken through our polymorphic xkcd defenses!
};


//////////////////////////////////////////////////////////////////////
/// @brief A using-alias that allows code wrapped in the pld namespace to be more clear.
/// @details The intent of this using alias is not to be used in any scope other than in the pld namespace.
/// This basically means that it is more clear to say, "void set_level(logging_level new_level)" rather than
/// "void set_level(level new_level);", the first being, IMHO, easier to read.
/// @see pld::level
//////////////////////////////////////////////////////////////////////
using logging_level = level;

//////////////////////////////////////////////////////////////////////
/// @brief A simple function that gets a logging level's name as a string.
/// @param level The logging level that is passed in to be converted into it's string counterpart.
/// @return std::string The name of the input logging level.
/// @see pld::logging_level
/// @see pld::level
//////////////////////////////////////////////////////////////////////
PLODD_API std::string level_name(logging_level level);

//////////////////////////////////////////////////////////////////////
/// @brief The abstract class all PLODD-compatible loggers inherit from.
//////////////////////////////////////////////////////////////////////
class PLODD_API base_logger {
    protected:
        //////////////////////////////////////////////////////////////////////
        /// @brief The name of the logger.
        ///
        /// @details The human-readable identifier for a logger. This is
        /// often included in a log so that the log's source can be identified.
        /// 
        /// This class member is tipically inherited as private (`class logger : 
        /// private base_logger {}`), and can be accessed by the `get_name`, 
        /// and `set_name` methods.
        ///
        /// @see get_name
        /// @see set_name
        //////////////////////////////////////////////////////////////////////
        std::string logger_name;

        //////////////////////////////////////////////////////////////////////
        /// @brief The logging level of the logger.
        ///
        /// @details Every logger should have<sup>1</sup> threshold at which 
        /// it will not log a requested log. This is simply for the sake of the 
        /// human reading the logs. Sometimes you don't want all the information
        /// sent to a logger to actually be logged. Sometimes you only want, 
        /// let's say all the WARN and ERROR logs to be logged, but not the 
        /// insignificant INFO and DEBUG logs to be logged. This member defines 
        /// that threshold.
        ///
        /// This class member, just like the logger_name, is tipically inherited
        /// private, but can be accessed by it's getter and setter functions.
        ///
        /// <sup>1</sup> All of this implementation specific. Not all loggers
        /// have to abide by these ideals. Nonetheless, all PLODD loggers do.
        ///
        /// @see logging_level
        /// @see get_level
        /// @see set_level
        //////////////////////////////////////////////////////////////////////
        logging_level logger_level;
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief Construct a new base logger object.
        /// 
        /// @param logger_name The name that will be given to the logger.
        /// @param logger_level The logging::level that will be assigned on contruction.
        ///
        /// @see ~base_logger
        /// @see set_name
        /// @see get_name
        /// @see set_level
        /// @see get_level
        //////////////////////////////////////////////////////////////////////
        base_logger(std::string logger_name, logging_level logger_level) : logger_name(logger_name), logger_level(logger_level){}

        //////////////////////////////////////////////////////////////////////
        /// @brief Destroy the base logger object.
        ///
        /// @see base_logger
        //////////////////////////////////////////////////////////////////////
        virtual ~base_logger(){}

        //////////////////////////////////////////////////////////////////////
        /// @brief Gets the name of the logger.
        ///
        /// @return std::string The name of the logger.
        ///
        /// @see set_name
        /// @see logger_name
        //////////////////////////////////////////////////////////////////////
        virtual std::string get_name();

        //////////////////////////////////////////////////////////////////////
        /// @brief Sets the name name of the logger.
        ///
        /// @param new_name The new name that will be given to the logger.
        ///
        /// @see get_name
        /// @see logger_name
        //////////////////////////////////////////////////////////////////////
        virtual void set_name(std::string new_name);

        //////////////////////////////////////////////////////////////////////
        /// @brief Gets the logging level.
        /// @return logging_level The current logging level
        /// @see set_level
        /// @see logging_level
        //////////////////////////////////////////////////////////////////////
        virtual logging_level get_level();

        //////////////////////////////////////////////////////////////////////
        /// @brief Sets the logging level.
        /// @param new_level The new level.
        /// @see get_level
        /// @see logging_level
        //////////////////////////////////////////////////////////////////////
        virtual void set_level(logging_level new_level);

        //////////////////////////////////////////////////////////////////////
        /// @brief The logger method that handels logs with the log level DEBUG.
        /// @param msg The message to be logged.
        //////////////////////////////////////////////////////////////////////
        virtual void debug(std::string msg) = 0;

        //////////////////////////////////////////////////////////////////////
        /// @brief The logger method that handels logs with the log level INFO.
        /// @param msg The message to be logged.
        //////////////////////////////////////////////////////////////////////
        virtual void info(std::string msg) = 0;

        //////////////////////////////////////////////////////////////////////
        /// @brief The logger method that handels logs with the log level WARN.
        /// @param msg The message to be logged.
        //////////////////////////////////////////////////////////////////////
        virtual void warn(std::string msg) = 0;

        //////////////////////////////////////////////////////////////////////
        /// @brief The logger method that handels logs with the log level ERROR.
        /// @param msg The message to be logged.
        //////////////////////////////////////////////////////////////////////
        virtual void error(std::string msg) = 0;
        
        //////////////////////////////////////////////////////////////////////
        /// @brief The formatting aware logger method that handels logs with the log level DEBUG.
        /// 
        /// @details This method is essentially a passthrough to the debug 
        /// function. This method's job (and every other formatted debug 
        /// method, i.e. infof, warnf, and errorf) is to pass the input
        /// (the format string and the packed format input) onto the {fmt} 
        /// libraries function `fmt::format` which accepts the noted input
        /// and produces the coresponding output.
        ///
        /// This means you can use the syntax provided by {fmt} to make
        /// formated logs.
        ///
        /// Example usage: 
        /// @code{.cpp}
        /// pld::console.debugf("{}, world! This my #{}st formmated log!", "Hello", 1);
        /// pld::console.warnf("Warning! This {1} be {0} fun.", "absurdly", "fun");
        /// @endcode
        ///
        /// Do notice this is a non-virtual function!
        /// This means that it will always be what it is. No inheritance
        /// changes that.
        ///
        /// @param fmt_str The message containing formatting options that is passed onto the fmt::format function for further processing.
        /// @param fmt_args The packed arguments that are passed onto.
        ///
        /// @see debug
        //////////////////////////////////////////////////////////////////////
        template<class... Args>
        void debugf(std::string fmt_str, const Args&... fmt_args){debug(fmt::format(fmt_str, fmt_args...).c_str());}

        //////////////////////////////////////////////////////////////////////
        /// @brief The formatting aware logger method that handels logs with the log level INFO.
        /// @see debugf
        //////////////////////////////////////////////////////////////////////
        template<class... Args>
        void infof(std::string fmt_str, const Args&... fmt_args){info(fmt::format(fmt_str, fmt_args...).c_str());}

        //////////////////////////////////////////////////////////////////////
        /// @brief The formatting aware logger method that handels logs with the log level WARN.
        /// @see debugf
        //////////////////////////////////////////////////////////////////////
        template<class... Args>
        void warnf(std::string fmt_str, const Args&... fmt_args){warn(fmt::format(fmt_str, fmt_args...).c_str());}

        //////////////////////////////////////////////////////////////////////
        /// @brief The formatting aware logger method that handels logs with the log level ERROR.
        /// @see debugf
        //////////////////////////////////////////////////////////////////////
        template<class... Args>
        void errorf(std::string fmt_str, const Args&... fmt_args){error(fmt::format(fmt_str, fmt_args...).c_str());}
};
} //pld

//TODO: Add an example inheritance from base_logger.

//////////////////////////////////////////////////////////////////////
/// @class base_logger
/// @details The base_logger is the mother of all loggers and contains 
/// everything a logger needs: a name, a logging level, and a few 
/// helper functions. Every PLODD-compatible logger is based off this 
/// logger, and a number of internal PLODD components use the it.
/// I.e. collections. It also provides log message formatting 
/// functionality. 
//////////////////////////////////////////////////////////////////////
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_BASE_H_