#include "utils.h"
#include <cctype>
#include <cmath>

namespace A65 {

	// Use regexes?
	std::vector<std::string> split_lines(std::string const& text)
	{

	}

	std::vector<std::string> split_words(std::string const& str)
	{

	}

	std::string lowercase(std::string const& str)
	{
		auto copy = str;
		for (auto& c : copy)
			c = static_cast<char>(tolower(c));
		return copy;
	}

	bool starts_with(std::string const& str, std::string const& sample)
	{
		if (str.length() < sample.length())
			return false;
		auto min_length = std::min(str.length(), sample.length());
		for (int i = 0; i < min_length; ++i)
		{
			if (str[i] != sample[i])
				return false;
		}
		return true;
	}

}

