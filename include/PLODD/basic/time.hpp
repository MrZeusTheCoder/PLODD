//////////////////////////////////////////////////////////////////////
/// @file get_time.hpp
/// @author Elijah Hopp (github.mrzeusthecoder@gmail.com)
/// @brief A time getter function for (semi-)internal use.
/// @version 0.1
/// @date 2019-07-22
/// 
/// @copyright Copyright (c) 2019 Elijah Hopp, No Rights Reserved
/// 
//////////////////////////////////////////////////////////////////////
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
    #include <iomanip>
    #include <chrono>
#endif
//Nonetheless, these are here. No matter what.
#include <iostream>

//#include "fmt/format.h"
//----------------------------------GET_TIME----------------------------------//
/*
//////////////////////////////////////////////////////////////////////
/// @brief Get the time by a format string.
///
/// Get the time based on the input format string. On non-Windows
/// platforms it uses the time_t structure and std::put_time.
/// The specialization for Windows only supports the getting of
/// the "%T" and "%D" time formats and uses internal Windows
/// functions and structures.
///
/// @param format The format of the returned string. On Windows it must be "%T" or "%D".
/// @return std::string The string representation of the requested format.
//////////////////////////////////////////////////////////////////////
*/
#ifdef _WIN32
    //TODO: Maybe do speedtest Windows once you have figured out Linux time.
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
    //TODO: YOU MUST OPTIMIZE THIS. EVEN MORE!!!!!! Callgrind said it accounted for over 70% of the function's call time.
    inline std::string get_time(){        
        time_t tea_time = std::time(0);
        tm* timely = std::localtime(&tea_time);
        return fmt::format("{}:{}:{}", timely->tm_hour, timely->tm_min, timely->tm_sec);
    }
    inline std::string get_date(){
        time_t tea_time = std::time(0);
        tm* timely = std::localtime(&tea_time);
        return fmt::format("{}-{}-{}", (timely->tm_year + 1900), (timely->tm_mon + 1), (timely->tm_mday));
    }
#endif
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_GET_TIME_H_