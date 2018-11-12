#pragma once

#include <vector>
#include <string>

namespace A65 {

	std::vector<std::string> split_lines(std::string const& text);

	std::vector<std::string> split_words(std::string const& str);

	std::string lowercase(std::string const& str);

	bool starts_with(std::string const& str, std::string const& sample);

}

