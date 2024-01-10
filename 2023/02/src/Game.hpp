#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <filesystem>
#include <map>

class Set
{
    public:
        int red{};
        int blue{};
        int green{};

        Set(int red, int blue, int green);
        Set(std::string_view set_string);
};


class Game
{
    private:
        const int ID;
        const std::vector<Set> sets{};
    
    public:
        Game(const int ID, const std::vector<Set>& sets);
        int getID() const;
        
        bool isPossible(Set startSet) const;
        
        static std::vector<Game> loadGamesFromFile(const std::filesystem::path& path);

        friend std::ostream& operator<<(std::ostream &out, const Game& data);
};

#endif // !GAME_HPP