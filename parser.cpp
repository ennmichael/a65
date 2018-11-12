#include "parser.h"
#include "utils.h"
#include <algorithm>

using namespace std::string_literals;

namespace A65 {

	namespace {

		bool is_literal(std::string const& word)
		{
			return word.length() > 1 && word[0] == hex_literal_start;
		}

		std::optional<Token> parse_punctuation(std::string const& word)
		{
			if (word == std::string(1, comma))
				return Comma {};
			if (word == std::string(1, open_curly_bracket))
				return OpenCurlyBracket {};
			if (word == std::string(1, closed_curly_bracket))
				return ClosedCurlyBracket {};
			return std::nullopt;
		}

		std::optional<Token> parse_literal(std::string const& word)
		{
			if (!is_literal(word))
				return std::nullopt;
			auto literal_digits = word.substr(1);
			std::optional<int> literal = parse_number(literal_digits);
			if (literal == std::nullopt)
				return InvalidToken {word, "Hex literal is not a number"s};
			if (literal_digits.length() <= 2)
				return OneByteLiteral {static_cast<char>(*literal)};
			if (literal_digits.length() <= 4)
				return TwoByteLiteral {}; // TODO
			return InvalidToken {word, "Hex literal can't be more than two bytes in size"s};
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
			if (word == "lda"s)
				return Instruction::LDA;
			return std::nullopt;
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
			       parse_name(lowercase_word).value_or(InvalidToken {})))));
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
		std::vector<std::string> token_words {""};
		for (auto const c : line)
		{
			if (isspace(c) && token_words.back() != "")
			{
				token_words.push_back("");
			}
			else if (c == comma || c == open_curly_bracket || c == closed_curly_bracket)
			{
				token_words.push_back(std::string(1, c));
				token_words.push_back("");
			}
			else
			{
				token_words.back().push_back(c);
			}
		}
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

