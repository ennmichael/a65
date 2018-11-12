#pragma once

#include <vector>
#include <string>
#include <optional>
#include <string_view>
#include <sstream>

namespace A65 {

    std::vector<std::string> split_lines(std::string const& text);

    std::string lowercase(std::string const& str);

    std::optional<int> parse_number(std::string const& str); // Might not need this, but will need something similar

}

