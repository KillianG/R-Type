//
// Created by prat on 07/11/18.
//

#define CATCH_CONFIG_MAIN

#include <Exception/Exception.hpp>
#include "catch.hpp"

void my_throw(const std::string &errorMsg) {
    throw rtype::Exception(errorMsg);
}

TEST_CASE("Exception") {
    SECTION("Creation") {
        std::string errorMsg = "It is broken";
        try {
            my_throw(errorMsg);
        }
        catch (rtype::Exception &ex) {
            REQUIRE(ex.getErrorMsg() == errorMsg);
        }
    }
}