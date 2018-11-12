#include "catch.hpp"
#include "../utils.h"

using namespace A65;
using namespace std::string_literals;

TEST_CASE("split_lines works")
{
    REQUIRE(split_lines("One\ntwo"s) == std::vector {"One"s, "two"s});
    REQUIRE(split_lines("One\ntwo\nthree  \n 4"s) == std::vector {"One"s, "two"s, "three  "s, " 4"s});
    REQUIRE(split_lines("One\n\n3") == std::vector {"One"s, ""s, "3"s});
    REQUIRE(split_lines("\nOne\n\n3") == std::vector {""s, "One"s, ""s, "3"s});
    REQUIRE(split_lines("\n\n\n\n3\n") == std::vector {""s, ""s, ""s, "3"s, ""s});
}

TEST_CASE("lowercase works")
{
    REQUIRE(lowercase("WHATEVERMAN"s) == "whateverman");
    REQUIRE(lowercase("A more complicated sentence, Containing whitespace and stuff. The CAPS are HerE") ==
            "a more complicated sentence, containing whitespace and stuff. the caps are here")
}

