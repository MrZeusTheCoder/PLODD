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
#include <sstream>
//----------------------------------GET_TIME----------------------------------//
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
inline std::string get_time(std::string format);

#ifdef _WIN32
    inline std::string get_time(std::string format){
        std::stringstream temp_ss;
        SYSTEMTIME local_time;
        //Retrive time:
        GetLocalTime(&local_time);
        //
        if(format.c_str() == "%T"){
            temp_ss << local_time.wHour << ":" local_time.wMinute << ":" << local_time.wSecond; //<< "." << local_time.WMilliseconds (You don't get mills Windows users. HA!)
        } elif(format.c_str() == "%D") {
            temp_ss << local_time.wYear << "/" << local_time.wMonth << "/" << local_time.wDay;
        }
    }
#else
    //TODO: YOU MUST OPTIMIZE THIS. Callgrind said it accounted for 70% of the function's call time.
    inline std::string get_time(std::string format){
        std::stringstream temp_ss;
        time_t temp_time = std::time(0);
        temp_ss << std::put_time(std::localtime(&temp_time), format.c_str());
        return temp_ss.str();
    }
#endif
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_GET_TIME_H_