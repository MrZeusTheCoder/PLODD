//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/file_logger.h"
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/file_logger.h>

#include <PLODD/multi_file_logger.h>
//--------------------------------FILE_LOGGER---------------------------------//
namespace logging {

multi_file_logger file{"PLODD", logging_level::INFO};

} //logging