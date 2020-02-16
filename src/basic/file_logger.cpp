//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/basic/file_logger.h"
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/file_logger.h>
#include <PLODD/basic/multi_file_logger.h>
#include <PLODD/basic/base.h>
//--------------------------------FILE_LOGGER---------------------------------//
namespace pld {

multi_file_logger file{"PLODD", logging_level::INFO};

} //logging