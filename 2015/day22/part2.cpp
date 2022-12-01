#include <iostream>
#include <fstream>
#include <queue>
#include <array>

class Enemy
{
public:
    int hp_;
    int damage_;

    Enemy(int h, int d)
        : hp_(h), damage_(d) {}

    Enemy() {}
};

class Player : public Enemy
{
public:
    int mana_;
    int armor_;
    int mana_spent_;
    std::array<int, 3> timers;

    Player(int h, int m, int a, int ms)
        : mana_(m), armor_(a), mana_spent_(ms)
    {
        hp_ = h;
    }

    Player() {}
};

void startTurn(std::pair<Player, Enemy> &current)
{
    // Start of player turn effects
    if (current.first.timers[0] > 0) // prevent infinite decrementing to not eventually underflow || ensure it stops decrementing at 0
    {
        current.first.timers[0]--;
    }
    if (current.first.timers[0] == 0) // if shield runs out
    {
        current.first.armor_ = 0;
    }

    if (current.first.timers[1] > 0) // if poison is active
    {
        current.second.hp_ -= 3;
        current.first.timers[1]--;
    }

    if (current.first.timers[2] > 0) // if recharge is active
    {
        current.first.mana_ += 101;
        current.first.timers[2]--;
    }
}

void missile(std::pair<Player, Enemy> &current)
{
    current.first.mana_spent_ += 53;
    current.first.mana_ -= 53;
    current.second.hp_ -= 4;
}

void drain(std::pair<Player, Enemy> &current)
{
    current.first.mana_spent_ += 73;
    current.first.mana_ -= 73;
    current.second.hp_ -= 2;
    current.first.hp_ += 2;
}

void shield(std::pair<Player, Enemy> &current)
{
    current.first.mana_spent_ += 113;
    current.first.mana_ -= 113;
    current.first.armor_ = 7;
    current.first.timers[0] = 6;
}

void poison(std::pair<Player, Enemy> &current)
{
    current.first.mana_spent_ += 173;
    current.first.mana_ -= 173;
    current.first.timers[1] = 6;
}

void recharge(std::pair<Player, Enemy> &current)
{
    current.first.mana_spent_ += 229;
    current.first.mana_ -= 229;
    current.first.timers[2] = 5;
}

int main()
{
    Enemy boss;

    {
        std::ifstream in("input");
        std::string line;

        std::getline(in, line);
        int hp = std::stoi(line.substr(line.find_last_of(' ')));

        std::getline(in, line);
        int damage = std::stoi(line.substr(line.find_last_of(' ')));

        boss = Enemy(hp, damage);
    }

    auto f = [](std::pair<Player, Enemy> t, std::pair<Player, Enemy> f) {
        if (t.first.mana_spent_ == f.first.mana_spent_)
            return t.first.mana_ < f.first.mana_;
        return t.first.mana_spent_ > f.first.mana_spent_;
    };

    std::priority_queue<
        std::pair<Player, Enemy>,
        std::vector<std::pair<Player, Enemy>>,
        decltype(f)>
        queue(f);

    queue.push({Player(50, 500, 0, 0), boss});

    while (!queue.empty())
    {
        std::pair<Player, Enemy> current = queue.top();
        queue.pop();

        current.first.hp_--;
        if (current.first.hp_ == 0) // if we died from hard mode
        {
            continue;
        }

        startTurn(current);

        if (current.second.hp_ <= 0) // if boss is dead after poison/after our turn we win
        {
            std::cout  << current.first.mana_spent_ << '\n';
            return 0;
        }

        const std::array<void (*)(std::pair<Player, Enemy> &), 5> spells = {missile, drain, shield, poison, recharge};
        const std::array<int, 5> costs = {53, 73, 113, 173, 229};

        // cast spell phase
        for (int i = 0; i < 5; i++)
        {
            if (costs[i] < current.first.mana_) // mana amount check
            {
                if (i < 2 || current.first.timers[i - 2] == 0) // if timer is non-existent or zero
                {
                    std::pair<Player, Enemy> caster = current;
                    spells[i](caster);

                    // start of boss's turn
                    startTurn(caster); // boss may die here, but I'm checking for lowest mana spent, so can't end here

                    int dmg = caster.second.damage_ - caster.first.armor_;
                    caster.first.hp_ -= dmg > 0 ? dmg : 1;

                    if (caster.first.hp_ > 0 || caster.second.hp_ <= 0) // if we ain't dead next turn or if boss is ded
                    {
                        queue.push(caster);
                    }
                }
            }
        }
    }

    return 0;
}