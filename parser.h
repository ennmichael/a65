#pragma once

#include <string>
#include <vector>
#include <variant>

namespace A65 {

	constexpr char comment_start = ';';

	enum class Instruction {
		LDA
	};

	enum class Keyword {
		define,
		macro
	};

	struct Name { std::string name; };

	struct OneByteLiteral { char byte; };

	struct TwoByteLiteral {
		char first_byte;
		char second_byte;
	};

	struct Comma { };

	struct Newline { };

	struct InvalidToken { std::string text; };

	using Token = std::variant<Instruction, Keyword, Name,
							   OneByteLiteral, TwoByteLiteral,
							   Comma, Newline, InvalidToken>;

	std::vector<Token> parse(std::string const& source_code);

}

