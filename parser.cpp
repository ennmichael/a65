#include "parser.h"
#include "utils.h"

namespace A65 {

	namespace {
	
		void parse_lines(std::string const& source_code, std::vector<Token>& tokens)
		{
		
		}

		void parse_words(std::string const& line, std::vector<Token>& tokens)
		{
		
		}

		Token find_token(std::string const& word)
		{
			if (word.)

			auto lowercase_word = lowercase(word);
			switch (lowercase_word)
			{
				case "lda": return Instruction::LDA;
				case "define": return Keyword::define;
				case "macro": return Keyword::macro;
				case ",": return Comma {};
				default: return Name {lowercase_word};
			}
		}
	
	}

	std::vector<Token> parse(std::string const& source_code)
	{
		std::vector<Token> tokens;
		auto const lines = split_lines(source_code);
		for (auto const& line : lines)
		{
			auto const words = split_words(line);
			for (auto const& word : words)
			{
				switch (word)
				{
				
				}
			}
			tokens.push_back(Newline{});
		}
	}

}

