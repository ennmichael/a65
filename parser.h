#pragma once

#include <string>
#include <vector>
#include <variant>

namespace A65 {

    char constexpr comma = ',';
    char constexpr open_curly_bracket = '{';
    char constexpr closed_curly_bracket = '}';
    char constexpr comment_start = ';';
    char constexpr hex_literal_start = '$';

    enum class Instruction {
        adc, and_, asl, bcc, bcs,
        beq, bit, bmi, bne, brk,
        bvc, bvs, clc, cld, cli,
        CLV, CMP, CPX, CPY, DEC,
        DEX, DEY, EOR, INC, INX,
        INY, jmp,
        jsr,
        LDA,
        ldx,
        ldy,
        lsr,
        nop,
        ora,
        pha,
        php,
        pla,
        plp,
        rol,
        ror,
        rti,
        rts,
        sbc,
        sec,
        sed,
        sei,
        sta,
        stx,
        sty,
        tax,
        tay,
        tsx,
        txa,
        txs,
        tya,
    };

    enum class Keyword {
        define,
        macro,
    };

    struct Name { std::string name; };

    struct OneByteLiteral { char byte; };

    struct TwoByteLiteral {
        char first_byte;
        char second_byte;
    };

    struct Comma { };

    struct OpenCurlyBracket {};

    struct ClosedCurlyBracket {};

    struct Newline { };

    struct InvalidToken {
        std::string text;
        std::string error;
    };

    using Token = std::variant<Instruction, Keyword, Name, OneByteLiteral, TwoByteLiteral,
                               Comma, OpenCurlyBracket, ClosedCurlyBracket, Newline, InvalidToken>;

    std::vector<std::string> split_token_words(std::string const& source_code);

    std::vector<Token> parse(std::string const& source_code);

}

