//  Copyright (C) Elijah Hopp 2020, No Rights Reserved.
//
//  Test file for "PLODD/ostream_logger.h".
//
//----------------------------------INCLUDES----------------------------------//
#include <PLODD/basic/ostream_logger.h>

#include <sstream>
#include <regex>

#define CATCH_CONFIG_MAIN 1
#include <catch-mini/catch-mini.hpp>
//----------------------------OSTREAM_LOGGER_TEST-----------------------------//
using namespace pld;

//------------------------TEST_OBJECTS-------------------------//
std::stringstream output_stream;

const std::regex PLODD_log_regex("(.*):(.*):(.*):(.*)");
const std::regex time_regex("\\[(?:.+):(?:.+):(?:.+)\\]");

//--------------------TEST_HELPER_FUNCTIONS--------------------//
bool test_log_fmt(std::string log_string, logging_level log_level);

int test_formatted_logger(ostream_logger& logger);

inline void clear_sstream(std::stringstream& stream){
    stream = std::stringstream();
}

//-------------------------TEST_CASES--------------------------//
TEST_CASE("Construction works properly"){
    ostream_logger logger(&output_stream, "TEST_LOGGER", level::DEBUG);
    REQUIRE(output_stream.str() == ""); //Make sure the output stream was untouched during ctor.
    REQUIRE(logger.get_name() == "TEST_LOGGER");
    REQUIRE(logger.get_level() == level::DEBUG);
}

TEST_CASE("Name setting works"){
    ostream_logger logger(&output_stream, "TEST_LOGGER", level::DEBUG);
    logger.set_name("NEW_NAME");
    REQUIRE(logger.get_name() == "NEW_NAME");
}

TEST_CASE("Level setting works"){
    ostream_logger logger(&output_stream, "TEST_LOGGER", level::ERROR);
    logger.set_level(level::DEBUG);
    REQUIRE(logger.get_level() == level::DEBUG);
    //TODO: Are these redundent?
    logger.set_level(level::INFO);
    REQUIRE(logger.get_level() == level::INFO);
    logger.set_level(level::WARN);
    REQUIRE(logger.get_level() == level::WARN);
    logger.set_level(level::ERROR);
    REQUIRE(logger.get_level() == level::ERROR);
}

TEST_CASE("Debug log is properly formed and prints correct number of logs"){
    ostream_logger logger(&output_stream, "TEST_LOGGER", level::DEBUG);
    REQUIRE(test_formatted_logger(logger) == 4);
}

TEST_CASE("Info log is properly formed and prints correct number of logs"){
    ostream_logger logger(&output_stream, "TEST_LOGGER", level::INFO);
    REQUIRE(test_formatted_logger(logger) == 3);
}

TEST_CASE("Warn log is properly formed and prints correct number of logs"){
    ostream_logger logger(&output_stream, "TEST_LOGGER", level::WARN);
    REQUIRE(test_formatted_logger(logger) == 2);
}

TEST_CASE("Error log is properly formed and prints correct number of logs"){
    ostream_logger logger(&output_stream, "TEST_LOGGER", level::ERROR);
    REQUIRE(test_formatted_logger(logger) == 1);
}
//----------------------HELPER_FUNCTION_IMPLEMENTATIONS-----------------------//
bool test_log_fmt(std::string log_string, logging_level log_level){
    //std::string log_string = log_stream.str(); //Strings passed into regex functions must not be temp strings, thus this line.
    unsigned int test_sum = 0;
    std::smatch log_match;

    if(std::regex_search(log_string, log_match, PLODD_log_regex)){
        std::string time_string = log_match[1].str();
        test_sum += (std::regex_search(time_string, time_regex)); //Check the debug log's time pattern.
        test_sum += (log_match[2].str() == "TEST_LOGGER"); //Logger name.
        test_sum += (log_match[3].str() == level_name(log_level)); //Logging level name.
        #if PLODD_NO_ANSI
            test_sum += (log_match[4].str() == "Heyo, world!");
        #else
            test_sum += (log_match[4].str() == "Heyo, world!\033[0m");
        #endif
    } else {
        throw std::runtime_error("Log is really garbled and the regex_search failed.");
    }

    if(test_sum == 4){
        return true;
    } else {
        return false;
    }
}

int test_formatted_logger(ostream_logger& logger){
    std::stringstream logger_output;
    logger.set_stream(&logger_output);
    unsigned int checks_passed = 0;
    //
    clear_sstream(logger_output); //For safety.
    logger.debug("Heyo, world!");
    checks_passed += (logger_output.str() == "") ? 0 : test_log_fmt(logger_output.str(), level::DEBUG);
    clear_sstream(logger_output);
    logger.info("Heyo, world!");
    checks_passed += (logger_output.str() == "") ? 0 : test_log_fmt(logger_output.str(), level::INFO);
    clear_sstream(logger_output);
    logger.warn("Heyo, world!");
    checks_passed += (logger_output.str() == "") ? 0 : test_log_fmt(logger_output.str(), level::WARN);
    clear_sstream(logger_output);
    logger.error("Heyo, world!");
    checks_passed += (logger_output.str() == "") ? 0 : test_log_fmt(logger_output.str(), level::ERROR);
    clear_sstream(logger_output);
    //
    return checks_passed;
}