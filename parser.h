#pragma once

#include <string>
#include <vector>
#include <variant>

namespace A65 {

    char constexpr comma = ',';
    char constexpr macro_start = '{';
    char constexpr macro_end = '}';
    char constexpr comment_start = ';';
    char constexpr hex_literal_marker = '$';
    char constexpr immediate_literal_marker = '#';

    enum class Instruction {
        adc, and_, asl, bcc, bcs,
        beq, bit, bmi, bne, brk,
        bvc, bvs, clc, cld, cli,
        clv, cmp, cpx, cpy, dec,
        dex, dey, eor, inc, inx,
        iny, jmp, jsr, lda, ldx,
        ldy, lsr, nop, ora, pha,
        php, pla, plp, rol, ror,
        rti, rts, sbc, sec, sed,
        sei, sta, stx, sty, tax,
        tay, tsx, txa, txs, tya,
    };

    enum class Keyword {
        define,
        macro,
    };

    struct Name { std::string text; };

    struct ImmediateLiteralMarker {};
    
    struct HexLiteral { std::string text; };

    struct Comma { };

    struct MacroStart {};

    struct MacroEnd {};

    struct Newline { };

    struct InvalidToken {
        std::string text;
        std::string error;
    };

    using Token = std::variant<Instruction, Keyword, Name, ImmediateLiteralMarker,
                               HexLiteral, Comma, MacroStart, MacroEnd, Newline, InvalidToken>;

    std::vector<std::string> split_token_words(std::string const& line);

    std::vector<Token> parse(std::string const& source_code);

    inline bool operator==(Name const& a, Name const& b)
    {
        return a.text == b.text;
    }

    inline bool operator==(ImmediateLiteralMarker, ImmediateLiteralMarker)
    {
        return true;
    }

    inline bool operator==(HexLiteral const& a, HexLiteral const& b)
    {
        return a.text == b.text;
    }

    inline bool operator==(Comma, Comma)
    {
        return true;
    }

    inline bool operator==(MacroStart, MacroStart)
    {
        return true;
    }

    inline bool operator==(MacroEnd, MacroEnd)
    {
        return true;
    }

    inline bool operator==(Newline, Newline)
    {
        return true;
    }

    inline bool operator==(InvalidToken a, InvalidToken b)
    {
        return a.text == b.text;
    }

}

