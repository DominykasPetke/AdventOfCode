#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

class Mob
{
public:
    int hp_;
    int armor_;
    int damage_;

    Mob(int h, int a, int d)
        : hp_(h), armor_(a), damage_(d) {}

    Mob() {}
};

class Player : public Mob
{
public:
    int gold_;

    Player(int h, int a, int d, int g)
        : gold_(g)
    {
        hp_ = h;
        armor_ = a;
        damage_ = d;
    }

    Player() {}
};

bool simulate(Mob boss, Player player)
{
    while (boss.hp_ > 0 && player.hp_ > 0)
    {
        int dmg = player.damage_ - boss.armor_;
        boss.hp_ -= dmg > 0 ? dmg : 1;

        dmg = boss.damage_ - player.armor_;
        player.hp_ -= dmg > 0 ? dmg : 1;
    }

    if (boss.hp_ <= 0)
        return true;

    return false;
}

int main()
{
    Mob boss;

    {
        std::ifstream in("input");
        std::string line;

        std::getline(in, line);
        int hp = std::stoi(line.substr(line.find_last_of(' ')));

        std::getline(in, line);
        int damage = std::stoi(line.substr(line.find_last_of(' ')));

        std::getline(in, line);
        int armor = std::stoi(line.substr(line.find_last_of(' ')));

        boss = Mob(hp, armor, damage);
    }

    std::vector<Player> possible_variations;

    std::vector<std::pair<int, int>> weapons = {{4, 8}, {5, 10}, {6, 25}, {7, 40}, {8, 74}};
    std::vector<std::pair<int, int>> armory = {{1, 13}, {2, 31}, {3, 53}, {4, 75}, {5, 102}};
    std::vector<std::tuple<int, int, int>> rings = {{1, 0, 25}, {2, 0, 50}, {3, 0, 100}, {0, 1, 20}, {0, 2, 40}, {0, 3, 80}};

    for (auto i : weapons)
    {
        Player noob = Player(100, 0, i.first, i.second);

        possible_variations.push_back(noob);

        for (auto j : armory)
        {
            Player yeet = noob;
            yeet.armor_ += j.first;
            yeet.gold_ += j.second;

            possible_variations.push_back(yeet);

            for (int x = 0; x < 6; x++)
            {
                Player ringy = yeet;

                ringy.damage_ += std::get<0>(rings[x]);
                ringy.armor_ += std::get<1>(rings[x]);
                ringy.gold_ += std::get<2>(rings[x]);

                possible_variations.push_back(ringy);

                for (int y = x + 1; y < 6; y++)
                {
                    Player ringed = ringy;

                    ringed.damage_ += std::get<0>(rings[y]);
                    ringed.armor_ += std::get<1>(rings[y]);
                    ringed.gold_ += std::get<2>(rings[y]);

                    possible_variations.push_back(ringed);
                }
            }
        }

        for (int x = 0; x < 6; x++)
        {
            Player ringy = noob;

            ringy.damage_ += std::get<0>(rings[x]);
            ringy.armor_ += std::get<1>(rings[x]);
            ringy.gold_ += std::get<2>(rings[x]);

            possible_variations.push_back(ringy);

            for (int y = x + 1; y < 6; y++)
            {
                Player ringed = ringy;

                ringed.damage_ += std::get<0>(rings[y]);
                ringed.armor_ += std::get<1>(rings[y]);
                ringed.gold_ += std::get<2>(rings[y]);

                possible_variations.push_back(ringed);
            }
        }
    }

    std::sort(possible_variations.begin(), possible_variations.end(), [](const Player &t, const Player &f) {
        return t.gold_ > f.gold_;
    });

    for (auto i : possible_variations)
    {
        if (!simulate(boss, i))
        {
            std::cout << i.gold_ << '\n';
            return 0;
        }
    }

    return 0;
}