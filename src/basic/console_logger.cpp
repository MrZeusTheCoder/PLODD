//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  The implementation file for "PLODD/basic/console_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/console_logger.h>
#include <PLODD/basic/base.h>
//-------------------------------CONSOLE_LOGGER-------------------------------//
namespace pld {

ostream_logger console{&std::cout, "PLODD", logging_level::DEBUG};

} //logging