#include "Game.hpp"
#include <filesystem>
#include <iostream>

int main(int argc, char** argv)
{
    std::filesystem::path game_data{"./input.txt"};
    const auto games = Game::loadGamesFromFile(game_data);
    
    std::cout << "Start Part 1" << "\n";
    const Set startSet{12, 14, 13};

    auto possibleGames{0};

    for (const auto& game : games)
    {
        if(game.isPossible(startSet))
        {
            possibleGames+= game.getID();
        }
    }

    std::cout << "Solution Part 1: " << possibleGames << "\n";
    std::cout << "Start Part 2" << "\n";

    unsigned int sum{0};

    for (const auto& game : games)
    {
        sum += game.getMinCubes();
    }

    std::cout << "Solution Part 2: " << sum << "\n";
}