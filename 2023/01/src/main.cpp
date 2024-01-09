#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

bool isNumber(const char c)
{
   return c >= '0' && c <= '9';
}

int getNumberInString(const std::string input_string)
{
    std::string numbers_s{};

    for (const char& c : input_string)
    {
        if(isNumber(c))
        {
            numbers_s += c;
        }
    }

    std::string number_s{};
    number_s.push_back(numbers_s.front());
    number_s.push_back(numbers_s.back());

    const auto number = std::stoi(number_s);
    return number;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <path of the input>" << std::endl;
        return 1;
    }

    const std::filesystem::path input_path{argv[1]};

    if (!std::filesystem::exists(input_path)) {
        std::cout << "Input file" << std::filesystem::weakly_canonical(input_path) << "does not exist" << std::endl;
        return 1;
    }

    std::ifstream input_file{input_path};

    long int sum{0};

    std::string line{};
    while(std::getline(input_file, line))
    {
        const auto number = getNumberInString(line);
        sum += number;
        line.clear();
    }

    std::cout << "Sum: " << sum << std::endl;;
}