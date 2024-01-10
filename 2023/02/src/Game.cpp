#include "Game.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <ranges>

std::vector<std::string> splitData(const std::string_view& sets_data, const std::string_view delimiter)
{
    auto view = sets_data
        | std::views::split(delimiter)
        | std::views::transform([](auto &&rng) {
                return std::string_view(&*rng.begin(), std::ranges::distance(rng));
    });

    std::vector<std::string> result{};
    for(const auto& v : view)
    {
        result.push_back(static_cast<std::string>(v));
    }
   
    return result;
};


Game::Game(const int ID, const std::vector<Set> &sets): ID{ID}, sets{sets}
{}
int Game::getID() const
{
    return this->ID;
};

std::vector<Game> Game::loadGamesFromFile(const std::filesystem::path &path)
{
    std::ifstream game_file{path};
    std::vector<Game> games{};

    std::string line{};
    while(std::getline(game_file, line))
    {
        // Split Game ID and Sets
        const auto game_data = line.substr(0, line.find_first_of(':'));
        const auto sets_data = line.substr(line.find_first_of(':') + 2, line.size());

        const auto ID = std::stoi(game_data.substr(game_data.find_first_of(' ')+1, game_data.size()));

        // Split sets
        const auto sets_string = splitData(sets_data, "; ");
        std::vector<Set> sets{};

        for( const auto& set_string : sets_string)
        {
            sets.push_back(Set(set_string));
        }
        games.push_back(Game{ID, sets});
    }

    return games;
}
bool Game::isPossible(Set startSet) const
{
    for(const auto& set : this->sets)
    {
        if(set.blue > startSet.blue || set.green > startSet.green || set.red > startSet.red)
        {
            return false;
        }
    }
    return true;
}
unsigned int Game::getMinCubes() const
{
    auto red{0};
    auto green{0};
    auto blue{0};

    for (const auto& set : this->sets)
    {
        if (set.red > red)
        {
            red = set.red;
        }
        if (set.green > green)
        {
            green = set.green;
        }
        if (set.blue > blue)
        {
            blue = set.blue;
        }
    }
    
    return red * green * blue;
};

std::ostream &operator<<(std::ostream &out, const Game &data)
{
    out << "Game " << data.ID << ": ";
    for(const auto& set : data.sets)
    {
        out << set.blue << " blue, " << set.green << " green, " << set.red << " red;";
    }
    return out;
}


Set::Set(int red, int blue, int green): red(red), blue(blue), green(green)
{
};

Set::Set(std::string_view set_string)
{
    // Split the values of each set
    for(const auto& cubes : splitData(set_string, ", "))
    {
        const auto data = splitData(cubes, " ");
        const std::string color = data[1];

        if(color == "red")
        {
            this->red = std::stoi(data[0]);
        }
        else if (color == "green")
        {
            this->green = std::stoi(data[0]);
        }
        else if (color == "blue")
        {
            this->blue = std::stoi(data[0]);
        }
    }
};
