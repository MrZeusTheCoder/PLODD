//////////////////////////////////////////////////////////////////////
/// @file time.hpp
/// @author Elijah Hopp (github.mrzeusthecoder@gmail.com)
/// @brief A thread safe time getter function intended for but not limited to internal use.
/// @version 0.0.0
/// @date 2020-02-28
/// 
/// @copyright Copyright (c) 2020 Elijah Hopp, No Rights Reserved
/// 
//////////////////////////////////////////////////////////////////////
//--------------------------------DEFINE_GUARD--------------------------------//
#ifndef PLODD_TS_GET_TIME_H_
#define PLODD_TS_GET_TIME_H_
//----------------------------------INCLUDES----------------------------------//
#ifdef _WIN32 
    #define WIN32_LEAN_AND_MEAN 1
    #define NOMINMAX 1
    #include <windows.h>
    #undef ERROR //Again, ligit Windows?
#else
    #include <chrono>
#endif
//Nonetheless, these are here. No matter what...
#include <iostream>
#include <thread>

#include "../fmt/format.h"
//------------------------------THREAD_SAFE_TIME------------------------------//
namespace pld {
namespace ts {

//Generating the time is expensive, so you just check if the elapsed seconds (since 1970... whatever) have changed,
//and if it hasn't use the old one.
static time_t last_read_time = 0;
static std::string last_generated_time;
static std::string last_generated_date;

//It's thread safe so all those have to be locked:
static std::mutex LRT_mutex;
static std::mutex LGT_mutex;
static std::mutex LGD_mutex;

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
    inline std::string get_time(){
        std::lock_guard<std::mutex> LRT_guard(LRT_mutex);
        std::lock_guard<std::mutex> LGT_guard(LGT_mutex);
        time_t tea_time = std::time(0);
        //
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
        std::lock_guard<std::mutex> LRT_guard(LRT_mutex);
        std::lock_guard<std::mutex> LGD_guard(LGD_mutex);
        time_t tea_time = std::time(0);
        //
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

} //ts
} //pld
//-----------------------------------END_IF-----------------------------------//
#endif //PLODD_TS_GET_TIME_H_