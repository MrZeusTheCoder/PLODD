//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  This file provides the needed base needs for any loggers.
// 
//--------------------------------DEFINE_GUARD--------------------------------//
#ifndef PLODD_BASE_H_
#define PLODD_BASE_H_
//----------------------------------INCLUDES----------------------------------//
#include <iostream>
#include "../fmt/format.h"
//----------------------------DEFINES_AND_STUFFING----------------------------//
#ifdef _WIN32
    #undef ERROR //Windows employee: "Why? Why not? Also, I took an online test that said I was a sadist, but that's unimportant."
    //^^^^^^^^^^ This will undefine any use of the word ERROR. This word is used throughout PLODD. :|
    #define NOMINMAX 1 //I like the "1". Feels more explicit.
    #define PLODD_NO_ANSI 1
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
/// @brief THE logging levels that define the volume at which you want to yell things.
//////////////////////////////////////////////////////////////////////
enum class level {
    DEBUG, //No one need that, right?
    INFO, //Helpful.
    WARN, //Calm down, it'll be fine.
    ERROR, //Oh no, he has broken through our polymorphic xkcd defenses!
};


//////////////////////////////////////////////////////////////////////
/// @brief A using-alias that allows code wrapped in the pld namespace to be more clear.
/// 
/// @details The intent of this using alias is not to be used in any scope other than in the pld namespace.
/// This basically means that it is more clear to say, "void set_level(level new_level)" rather than
/// "void set_level(logging_level new_level);", which IMHO is easier to read.
//////////////////////////////////////////////////////////////////////
using logging_level = level;

//////////////////////////////////////////////////////////////////////
/// @brief A simple function that converts a
/// 
/// @param level 
/// @return std::string 
//////////////////////////////////////////////////////////////////////
std::string level_name(logging_level level);

class base_logger {
    protected:
        std::string logger_name;
        logging_level logger_level;
    public:
        base_logger(std::string logger_name, logging_level logger_level) : logger_name(logger_name), logger_level(logger_level){}
        virtual ~base_logger(){}
        virtual void set_level(logging_level new_level);
        virtual void set_name(std::string new_name);
        virtual logging_level get_level();
        virtual std::string get_name();
        virtual void debug(std::string msg) = 0;
        virtual void info(std::string msg) = 0;
        virtual void warn(std::string msg) = 0;
        virtual void error(std::string msg) = 0;
        template<class... Args>
        void debugf(std::string fmt_str, const Args&... fmt_args){debug(fmt::format(fmt_str, fmt_args...).c_str());}
        template<class... Args>
        void infof(std::string fmt_str, const Args&... fmt_args){info(fmt::format(fmt_str, fmt_args...).c_str());}
        template<class... Args>
        void warnf(std::string fmt_str, const Args&... fmt_args){warn(fmt::format(fmt_str, fmt_args...).c_str());}
        template<class... Args>
        void errorf(std::string fmt_str, const Args&... fmt_args){error(fmt::format(fmt_str, fmt_args...).c_str());}
};
} //pld


//---------------------------------SFML_PLODD---------------------------------//
#ifdef SFML_PLODD
namespace pld {

#include "fmt/format.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

template<>
struct fmt::formatter<sf::Vector2f>{
    template<typename ParseContext>
    constexpr ParseContext& parse(ParseContext& ctx){
        return ctx.begin();
    }
    template<typename FormatContext>
    FormatContext& format(const sf::Vector2f& vec, FormatContext& ctx){
        return fmt::format_to(ctx.out(), "({0}, {1})", vec.x, vec.y);
    }
};

template<>
struct fmt::formatter<sf::Color>{
    template<typename ParseContext>
    constexpr ParseContext& parse(ParseContext& ctx){
        return ctx.begin();
    }
    template<typename FormatContext>
    FormatContext& format(const sf::Color& color, FormatContext& ctx){
        return fmt::format_to(ctx.out(), "({0}, {1}, {2}, {3})", color.r, color.g, color.b, color.a);
    }
};
} //pld
#endif
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_BASE_H_