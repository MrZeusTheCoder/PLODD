//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  Logggggggggssss tostd::coutcuzwhynot? Haz me c0ff33. p1z I h4z n33d
//  m0n3y. d0n4t3 n0w.
// 
/*--------------------------------DEFINE_GUARD--------------------------------*/
#ifndef PLODD_CONSOLE_LOGGER_H_
#define PLODD_CONSOLE_LOGGER_H_
/*----------------------------------INCLUDES----------------------------------*/
#include <PLODD/ostream_logger.h>
#include <iostream>
//-------------------------------CONSOLE_LOGGER-------------------------------//
namespace logging {

//Exposes a console logger for use like so: "logging::console.info("p1z h4z m3 m0n3y... p1z?");"
extern ostream_logger console;

} //logging
/*-----------------------------------END_IF-----------------------------------*/
#endif //PLODD_CONSOLE_LOGGER_H_