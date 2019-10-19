//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The file logger header file.
//
/*--------------------------------DEFINE_GUARD--------------------------------*/
#ifndef PLODD_FILE_LOGGER_H_
#define PLODD_FILE_LOGGER_H_
/*----------------------------------INCLUDES----------------------------------*/
#include <PLODD/multi_file_logger.h>
/*--------------------------------FILE_LOGGER---------------------------------*/
namespace logging {

//Exposes a file logger for use like so: "logging::file.info("fake, helpful info.");"
extern multi_file_logger file;

} //logging
/*-----------------------------------END_IF-----------------------------------*/
#endif //PLODD_FILE_LOGGER_H_