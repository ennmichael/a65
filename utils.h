#pragma once

#include <vector>
#include <string>
#include <optional>
#include <string_view>
#include <sstream>

namespace A65 {

    std::vector<std::string> split_lines(std::string const& text);

    std::vector<std::string> split_words(std::string const& str);

    std::vector<std::string> split_string(std::string const& str, std::string const& delims);

    std::string lowercase(std::string const& str);

    std::optional<int> parse_number(std::string_view view);

}

