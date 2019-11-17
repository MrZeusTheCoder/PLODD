//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/console_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/console_logger.h>
//-------------------------------CONSOLE_LOGGER-------------------------------//
namespace logging {

ostream_logger console{&std::cout, "PLODD", logging_level::DEBUG};

} //logging