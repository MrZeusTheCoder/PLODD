//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  Test file for "PLODD/include/base.h".
//
/*----------------------------------INCLUDES----------------------------------*/
#include <PLODD/base.h>

#include <catch2/catch.hpp>
/*-----------------------------BASE_LOGGER_TESTS------------------------------*/
using namespace logging;

SCENARIO("A logger needs colour codes.", "[ansi_colours]"){
    GIVEN("The colours defined as constants."){
        using namespace logging::colours;
        REQUIRE(reset == "\033[0m");
        REQUIRE(gray == "\033[0;37m");
        REQUIRE(white == "\033[1;37m");
        REQUIRE(yellow == "\033[1;33m");
        REQUIRE(red == "\033[1;31m");
        REQUIRE(reverse_vid == "\033[7m");
    }
}

SCENARIO("Someone needs the names of logging levels as strings.", "[level_name]"){
    GIVEN("A number of logging levels to test."){
        REQUIRE(level_name(level::DEBUG) == "DEBUG");
        REQUIRE(level_name(level::INFO) == "INFO");
        REQUIRE(level_name(level::WARN) == "WARN");
        REQUIRE(level_name(level::ERROR) == "ERROR");
    }
}