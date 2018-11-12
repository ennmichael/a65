#include "parser.h"
#include "utils.h"
#include <cassert>
#include <algorithm>
#include <unordered_map>

using namespace std::string_literals;

namespace A65 {

    namespace {

        std::optional<Token> parse_punctuation(std::string const& word)
        {
            if (word.length() != 1)
                return std::nullopt;

            static std::unordered_map<char, Token> lookup_table
            {
                {comma, Comma {}},
                {macro_start, MacroStart {}},
                {macro_end, MacroEnd {}},
                {immediate_literal_marker, ImmediateLiteralMarker {}},
            };

            if (!lookup_table.count(word.front()))
                return std::nullopt;
            return lookup_table.at(word.front());
        }

        bool are_valid_hex_digits(std::string const& digits)
        {
            return std::all_of(digits.cbegin(), digits.cend(), isxdigit);
        }

        std::optional<Token> parse_literal(std::string const& word)
        {
            if (word.length() > 1 && word.front() == hex_literal_marker)
            {
                auto digits = word.substr(1);
                if (are_valid_hex_digits(digits))
                    return HexLiteral {digits};
                return InvalidToken {word, "Invalid hex literal"};
            }
            return std::nullopt;
        }

        std::optional<Token> parse_keyword(std::string const& word)
        {
            if (word == "define"s)
                return Keyword::define;
            if (word == "macro"s)
                return Keyword::macro;
            return std::nullopt;
        }

        std::optional<Token> parse_instruction(std::string const& word)
        {
            static std::unordered_map<std::string, Instruction> const lookup_table
            {
                {"adc"s, Instruction::adc}, {"and"s, Instruction::and_},
                {"asl"s, Instruction::asl}, {"bcc"s, Instruction::bcc},
                {"bcs"s, Instruction::bcs}, {"beq"s, Instruction::beq},
                {"bit"s, Instruction::bit}, {"bmi"s, Instruction::bmi},
                {"bne"s, Instruction::bne}, {"brk"s, Instruction::brk},
                {"bvc"s, Instruction::bvc}, {"bvs"s, Instruction::bvs},
                {"clc"s, Instruction::clc}, {"cld"s, Instruction::cld},
                {"cli"s, Instruction::cli}, {"clv"s, Instruction::clv},
                {"cmp"s, Instruction::cmp}, {"cpx"s, Instruction::cpx},
                {"cpy"s, Instruction::cpy}, {"dec"s, Instruction::dec},
                {"dex"s, Instruction::dex}, {"dey"s, Instruction::dey},
                {"eor"s, Instruction::eor}, {"inc"s, Instruction::inc},
                {"inx"s, Instruction::inx}, {"iny"s, Instruction::iny},
                {"jmp"s, Instruction::jmp}, {"jsr"s, Instruction::jsr},
                {"lda"s, Instruction::lda}, {"ldx"s, Instruction::ldx},
                {"ldy"s, Instruction::ldy}, {"lsr"s, Instruction::lsr},
                {"nop"s, Instruction::nop}, {"ora"s, Instruction::ora},
                {"pha"s, Instruction::pha}, {"php"s, Instruction::php},
                {"pla"s, Instruction::pla}, {"plp"s, Instruction::plp},
                {"rol"s, Instruction::rol}, {"ror"s, Instruction::ror},
                {"rti"s, Instruction::rti}, {"rts"s, Instruction::rts},
                {"sbc"s, Instruction::sbc}, {"sec"s, Instruction::sec},
                {"sed"s, Instruction::sed}, {"sei"s, Instruction::sei},
                {"sta"s, Instruction::sta}, {"stx"s, Instruction::stx},
                {"sty"s, Instruction::sty}, {"tax"s, Instruction::tax},
                {"tay"s, Instruction::tay}, {"tsx"s, Instruction::tsx},
                {"txa"s, Instruction::txa}, {"txs"s, Instruction::txs},
                {"tya"s, Instruction::tya},
            };

            if (lookup_table.count(word) == 0)
                return std::nullopt;
            return lookup_table.at(word);
        }

        bool is_valid_name(std::string const& word)
        {
            return std::all_of(word.cbegin(), word.cend(), isalnum);
        }

        std::optional<Token> parse_name(std::string const& word)
        {
            if (!is_valid_name(word))
                return std::nullopt;
            return Name {word};
        }

        Token parse_token(std::string const& word)
        {
            auto const lowercase_word = lowercase(word);
            return parse_punctuation(lowercase_word).value_or(
                   parse_literal(lowercase_word).value_or(
                   parse_keyword(lowercase_word).value_or(
                   parse_instruction(lowercase_word).value_or(
                   parse_name(lowercase_word).value_or(InvalidToken {word, "Invalid name"})))));
        }

        void parse_words(std::string const& line, std::vector<Token>& tokens)
        {
            auto const words = split_token_words(line);
            for (auto const& word : words)
                tokens.push_back(parse_token(word));
        }
    
        void parse_lines(std::string const& source_code, std::vector<Token>& tokens)
        {
            auto const lines = split_lines(source_code);
            for (auto const& line : lines)
            {
                if (line != "")
                    parse_words(line, tokens);
                tokens.push_back(Newline{});
            }
        }

    }

    std::vector<std::string> split_token_words(std::string const& line)
    {
        // line is not expected to end with '\n'

        std::vector<std::string> token_words {""};
        for (auto const c : line)
        {
            if (c == comment_start)
            {
                // FIXME This is a bit of a hack
                // Look for a nicer way to do this
                break;
            }
            else if (isspace(c))
            {
                if (token_words.back() != "")
                    token_words.push_back("");
            }
            else if (c == comma || c == macro_start || c == macro_end || c == immediate_literal_marker)
            {
                if (token_words.back() == "")
                    token_words.back() = std::string(1, c);
                else
                    token_words.push_back(std::string(1, c));
                token_words.push_back("");
            }
            else
            {
                token_words.back().push_back(c);
            }
        }
        if (token_words.back() == "")
            token_words.pop_back();
        return token_words;
    }

    std::vector<Token> parse(std::string const& source_code)
    {
        std::vector<Token> tokens;
        parse_lines(source_code, tokens);
        parse_words(source_code, tokens);
        return tokens;
    }

}

