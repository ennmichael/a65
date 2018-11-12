#include "catch.hpp"
#include "../parser.h"

using namespace A65;
using namespace std::string_literals;

namespace {

    auto constexpr example_source_1 = "define A $32\n"
                                      "define B $42\n"
                                      "macro M {}\n"
                                      "\n"
                                      "LDA #$FF\n"
                                      "LDX $12\n"
                                      "LDY $1232\n"
                                      "AND #$25, X\n"
                                      "\n"
                                      "macro MM\n"
                                      "{\n"
                                      "  CLC\n"
                                      "  SED\n"
                                      "  BIT $1233, Y\n"
                                      "}\n"
                                      "\n"
                                      "\n"
                                      "M\n"
                                      "MM\n";

}

// TODO Test comments

TEST_CASE("split_token_words() works")
{
    REQUIRE(split_token_words("define A $32"s) == std::vector {"define"s, "A"s, "$32"s});
    REQUIRE(split_token_words("define B $42\n"s) == std::vector {"define"s, "B"s, "$42"s});
    REQUIRE(split_token_words("   macro M    {       } "s) == std::vector {"macro"s, "M"s, "{"s, "}"s});
    REQUIRE(split_token_words("LDA   #$FF "s) == std::vector {"LDA"s, "#"s, "$FF"s});
    REQUIRE(split_token_words("LDA   #$ F f "s) == std::vector {"LDA"s, "#"s, "$"s, "F"s, "f"s});
    REQUIRE(split_token_words("AND #$25, X") == std::vector {"AND"s, "#"s, "$25"s, ","s, "X"s});
    REQUIRE(split_token_words("\t\tAND #$25  \t, X") == std::vector {"AND"s, "#"s, "$25"s, ","s, "X"s});
    REQUIRE(split_token_words("BIT   someValue , Y") == std::vector {"BIT"s, "someValue"s, ","s, "Y"s});
    REQUIRE(split_token_words("B I\tT   someValue , Y") == std::vector {"B"s, "I"s, "T"s, "someValue"s, ","s, "Y"s});
}

TEST_CASE("parse() works")
{

}

