//  Copyright (C) Elijah Hopp 2020, No Rights Reserved.
//
//  Test file for "PLODD/ostream_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/uf_ostream_logger.h>

#include <sstream>

#include <catch2/catch.hpp>
//----------------------UNFORMATTED_OSTREAM_LOGGER_TEST-----------------------//
using namespace pld;

inline void clear_sstream(std::stringstream& stream){
    stream = std::stringstream();
}

int test_unformatted_logger(uf_ostream_logger& logger){
    std::stringstream logger_output;
    logger.set_stream(&logger_output);
    unsigned int checks_passed = 0;
    //
    clear_sstream(logger_output); //For safety.
    logger.debug("Heyo, world!");
    checks_passed += (logger_output.str() == "Heyo, world!") ? 1 : 0;
    clear_sstream(logger_output);
    logger.info("Heyo, world!");
    checks_passed += (logger_output.str() == "Heyo, world!") ? 1 : 0;
    clear_sstream(logger_output);
    logger.warn("Heyo, world!");
    checks_passed += (logger_output.str() == "Heyo, world!") ? 1 : 0;
    clear_sstream(logger_output);
    logger.error("Heyo, world!");
    checks_passed += (logger_output.str() == "Heyo, world!") ? 1 : 0;
    clear_sstream(logger_output);
    //
    return checks_passed;
}

SCENARIO("Someone needs a working unformatted ostream logger", "[uf_ostream_logger]"){
    GIVEN("An unformatted ostream logger and a stringstream"){
        std::stringstream output_stream;
        uf_ostream_logger logger(&output_stream, "TEST_LOGGER", level::DEBUG);
        REQUIRE(output_stream.str() == "");
        REQUIRE(logger.get_name() == "TEST_LOGGER");
        REQUIRE(logger.get_level() == level::DEBUG);

        WHEN("A debug log call is made"){
            logger.set_level(logging_level::DEBUG);
            REQUIRE(logger.get_level() == level::DEBUG);
            REQUIRE(test_unformatted_logger(logger) == 4);
        }
        WHEN("An info log call is made"){
            logger.set_level(logging_level::INFO);
            REQUIRE(logger.get_level() == level::INFO);
            REQUIRE(test_unformatted_logger(logger) == 3);
        }
        WHEN("A warn log call is made"){
            logger.set_level(logging_level::WARN);
            REQUIRE(logger.get_level() == level::WARN);
            REQUIRE(test_unformatted_logger(logger) == 2);
        }
        WHEN("An error log call is made"){
            logger.set_level(logging_level::ERROR);
            REQUIRE(logger.get_level() == level::ERROR);
            REQUIRE(test_unformatted_logger(logger) == 1);
        }
    }
}