//  Copyright (C) Elijah Hopp 2019, All Rights Reserved.
//
//  Test file for "PLODD/include/base.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/base.h>

#include <type_traits>

#include <catch2/catch.hpp>
#include <stringy/stringy.hpp>
//-----------------------------BASE_LOGGER_TESTS------------------------------//
using namespace pld;

SCENARIO("A logger needs colour codes.", "[ansi_colours]"){
    GIVEN("The colours defined as constants."){
        using namespace pld::colours;
        REQUIRE(stringy::make_hex_string(reset) == "\\x1b\\x5b\\x30\\x6d");
        REQUIRE(stringy::make_hex_string(gray) == "\\x1b\\x5b\\x30\\x3b\\x33\\x37\\x6d");
        REQUIRE(stringy::make_hex_string(white) == "\\x1b\\x5b\\x31\\x3b\\x33\\x37\\x6d");
        REQUIRE(stringy::make_hex_string(yellow) == "\\x1b\\x5b\\x31\\x3b\\x33\\x33\\x6d");
        REQUIRE(stringy::make_hex_string(red) == "\\x1b\\x5b\\x31\\x3b\\x33\\x31\\x6d");
        REQUIRE(stringy::make_hex_string(reverse_vid) == "\\x1b\\x5b\\x37\\x6d");
    }
}


SCENARIO("Someone needs the logging levels.", "[logging_levels]"){
    GIVEN("The level_name function."){
        REQUIRE(level_name(level::DEBUG) == "DEBUG");
        REQUIRE(level_name(level::INFO) == "INFO");
        REQUIRE(level_name(level::WARN) == "WARN");
        REQUIRE(level_name(level::ERROR) == "ERROR");
    }
    GIVEN("The logging_level type alias."){
        REQUIRE(std::is_same<level, logging_level>::value);
    }
}