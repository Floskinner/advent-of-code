#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string_view>
#include <vector>
#include <iterator>

template<typename It>
auto getIntIterators(const std::string_view& line) -> std::optional<std::vector<std::pair<It, It>>>
{
    std::cout << "Line: " << line << '\n';
    auto numbers = std::vector<std::pair<It, It>>{};
    const auto begin_digit = std::find_if(line.begin(), line.end(), [](const auto& c) { return std::isdigit(c); });

    if (begin_digit == line.end()) {
        return std::nullopt; // Early return if no digits found
    }

    auto end_digit = std::find_if_not(begin_digit, line.end(), [](const auto& c) { return std::isdigit(c); });
    numbers.push_back({ begin_digit, end_digit });

    // Recursive call starts here
    if (end_digit!= line.end() && end_digit+1 != line.end()) {
        auto recursive_result = getIntIterators<It>(line.substr(end_digit - line.begin() + 1));
        if (recursive_result.has_value()) {
            numbers.insert(numbers.end(), recursive_result.value().begin(), recursive_result.value().end());
        }
    }
    return numbers;
}

const std::vector<unsigned int> numbers_adjacent_to_symbol(const std::string_view& before_line, const std::string_view& line, const std::string_view& after_line)
{
    auto numbers = std::vector<unsigned int>{};

    std::cout << "Before: " << before_line << '\n';
    // std::cout << "Line: " << line << '\n';
    // std::cout << "After: " << after_line << '\n';

    const auto before_numbers = getIntIterators<std::string_view::const_iterator>(before_line);
    for (const auto& number : before_numbers.value()) {
        std::cout << "Before: ";
        std::copy(number.first, number.second, std::ostream_iterator<char>(std::cout));
        std::cout << '\n';
    }
    exit(EXIT_SUCCESS);
    return numbers;
};

int main(int argc, char** argv)
{
    const auto engine_data = std::filesystem::path{ "./input.txt" };
    auto data_stream = std::ifstream{ engine_data };
    
    auto line_before = std::string{};
    auto line = std::string{};
    auto line_after = std::string{};

    while (data_stream) {
        if (line_before.empty()) {
            std::getline(data_stream, line_before);
            continue;
        }
        if (line.empty()) {
            std::getline(data_stream, line);
            continue;
        }

        std::getline(data_stream, line_after);

        numbers_adjacent_to_symbol(line_before, line, line_after);

    }
}