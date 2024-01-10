#include "Game.hpp"
#include <filesystem>
#include <iostream>

int main(int argc, char** argv)
{
    std::filesystem::path game_data{"./input.txt"};
    const Set startSet{12, 14, 13};

    const auto games = Game::loadGamesFromFile(game_data);

    for (const auto& game : games)
    {
        std::cout << game << "\n";
    }

    auto possibleGames{0};

    for (const auto& game : games)
    {
        if(game.isPossible(startSet))
        {
            possibleGames+= game.getID();
        }
    }

    std::cout << possibleGames << "\n";
}