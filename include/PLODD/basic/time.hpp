////////////////////////////////////////////////////////////////////////////////
/// @file time.hpp
/// @author Elijah Hopp (github.mrzeusthecoder@gmail.com)
/// @brief A time getter intended for but not limited to internal use.
/// @version 0.0.0
/// @date 2020-02-28
/// 
/// @copyright Copyright (c) 2020 Elijah Hopp, No Rights Reserved
/// 
////////////////////////////////////////////////////////////////////////////////
//--------------------------------DEFINE_GUARD--------------------------------//
#ifndef PLODD_GET_TIME_H_
#define PLODD_GET_TIME_H_
//----------------------------------INCLUDES----------------------------------//
#ifdef _WIN32 //Curse Windows. WAIT... Curses doesn't work ON WINDOWS... HA!
    #define WIN32_LEAN_AND_MEAN 1
    #define NOMINMAX 1
    #include <windows.h>
    #undef ERROR //Again, ligit Windows?
#else
    #include <chrono>
#endif

#include <iostream>

#include "../../fmt/format.h"
//------------------------------------TIME------------------------------------//
namespace pld {
//Generating the time is expensive, so you just check if the elapsed seconds (since 1970... whatever) have changed,
//and if it hasn't use the old one.
static time_t last_read_time = 0;
static std::string last_generated_time;
static std::string last_generated_date;

#ifdef _WIN32
    //TODO: Maybe do speedtest Windows.
    inline std::string get_time(){
        SYSTEMTIME local_time;
        GetLocalTime(&local_time);
        return fmt::format("{}:{}:{}", local_time.wHour, local_time.wMinute, local_time.wSecond);
    }
    inline std::string get_date(){
        SYSTEMTIME local_time;
        GetLocalTime(&local_time);
        return fmt::format("{}-{}-{}", local_time.wYear, local_time.wMonth, local_time.wDay);
    }
#else
    inline std::string get_time(){
        time_t tea_time = std::time(0);
        if(tea_time == last_read_time){
            return last_generated_time;
        } else {
            tm* timely = std::localtime(&tea_time);
            last_generated_time = fmt::format("{}:{}:{}", timely->tm_hour, timely->tm_min, timely->tm_sec);
            last_read_time = tea_time;
            return last_generated_time;
        }
    }
    inline std::string get_date(){
        time_t tea_time = std::time(0);
        if(tea_time == last_read_time){
            return last_generated_date;
        } else {
            tm* timely = std::localtime(&tea_time);
            last_generated_date = fmt::format("{}-{}-{}", (timely->tm_year + 1900), (timely->tm_mon + 1), (timely->tm_mday));
            last_read_time = tea_time;
            return last_generated_date;
        }
        
    }
#endif

} //pld
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_GET_TIME_H_