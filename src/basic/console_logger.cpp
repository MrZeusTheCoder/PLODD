//  Copyright (C) Elijah Hopp 2020, No Rights Reserved.
//
//  The implementation file for "PLODD/basic/console_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/console_logger.h>
#include <PLODD/basic/base.h>
//-------------------------------CONSOLE_LOGGER-------------------------------//
namespace pld {

ostream_logger console{&std::cout, "CONSOLE", logging_level::DEBUG};

} //logging