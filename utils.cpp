#include "utils.h"
#include <cctype>
#include <cmath>

using namespace std::string_literals;

namespace A65 {


    std::vector<std::string> split_lines(std::string const& text)
    {
        std::vector<std::string> result {""s};
        for (auto const c : text)
        {
            if (c == '\n')
                result.push_back(""s);
            else
                result.back().push_back(c);
        }
        return result;
    }

    std::string lowercase(std::string const& str)
    {
        auto copy = str;
        for (auto& c : copy)
            c = static_cast<char>(tolower(c));
        return copy;
    }

    std::optional<int> parse_number(std::string const& str)
    {
        std::stringstream ss(str);
        int result;
        ss >> result;
        return (ss.fail()) ? std::nullopt : std::optional(result);
    }

}

