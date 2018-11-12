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
                                      "LDY $12325\n"
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
                                      "MM";

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
    auto const tokens = parse(example_source_1);
    REQUIRE(tokens == std::vector<Token> {
        Keyword::define, Name {"a"s}, HexLiteral {"32"}, Newline {},
        Keyword::define, Name {"b"s}, HexLiteral {"42"}, Newline {},
        Keyword::macro, Name {"m"s}, MacroStart {}, MacroEnd {}, Newline {},
        Newline {},
        Instruction::lda, ImmediateLiteralMarker {}, HexLiteral {"ff"s}, Newline {},
        Instruction::ldx, HexLiteral {"12"s}, Newline {},
        Instruction::ldy, HexLiteral {"12325"s}, Newline {},
        Instruction::and_, ImmediateLiteralMarker {}, HexLiteral {"25"s}, Comma {}, Name {"x"s}, Newline {},
        Newline {},
        Keyword::macro, Name {"mm"s}, Newline {},
        MacroStart {}, Newline {},
        Instruction::clc, Newline {},
        Instruction::sed, Newline {},
        Instruction::bit, HexLiteral {"1233"s}, Comma {}, Name {"y"s}, Newline{},
        MacroEnd {}, Newline {},
        Newline {},
        Newline {},
        Name {"m"s}, Newline {},
        Name {"mm"s}, Newline {},
    });
}

