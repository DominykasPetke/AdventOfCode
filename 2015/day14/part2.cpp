#include <iostream>
#include <fstream>
#include <vector>

class Reindeer
{
    std::string name_;
    unsigned int speed_;
    unsigned int time_;
    unsigned int rest_time_;

    bool resting_;
    unsigned int remaining_;

public:
    unsigned int distance_;
    unsigned int points_;

    Reindeer(std::string name, unsigned int speed, unsigned int time, unsigned int rest_time)
        : name_(name), speed_(speed), time_(time), rest_time_(rest_time), resting_(false), remaining_(time), distance_(0), points_(0) {}

    void simulate()
    {
        if (!resting_)
        {
            distance_ += speed_;
        }

        remaining_--;

        if (remaining_ == 0)
        {
            resting_ = !resting_;

            if (resting_)
            {
                remaining_ = rest_time_;
            }
            else
            {
                remaining_ = time_;
            }
        }
    }
};

int main()
{
    std::vector<Reindeer> deers;

    {
        std::ifstream in("input");
        std::string line;

        while (std::getline(in, line))
        {
            std::vector<std::string> values = [&line]() {
                size_t pos = 0;
                std::string token;

                std::vector<std::string> ret;

                while ((pos = line.find(" ")) != std::string::npos)
                {
                    token = line.substr(0, pos);
                    ret.push_back(token);
                    line.erase(0, pos + 1);
                }

                ret.push_back(line);

                return ret;
            }();

            deers.push_back({values[0], std::stoi(values[3]), std::stoi(values[6]), std::stoi(values[13])});
        }
    }

    for (int i = 0; i < 2503; i++)
    {
        for (auto &r : deers)
        {
            r.simulate();
        }

        unsigned int max = 0;
        std::vector<size_t> ids;

        for (size_t i = 0; i < deers.size(); i++)
        {
            Reindeer deer = deers[i];

            if (deer.distance_ == max)
            {
                ids.push_back(i);
            }
            else if (deer.distance_ > max)
            {
                max = deer.distance_;
                ids = {i};
            }
        }

        for (int i : ids)
        {
            deers[i].points_++;
        }
    }

    unsigned int max = 0;

    for (auto i : deers)
    {
        if (i.points_ > max)
        {
            max = i.points_;
        }
    }

    std::cout << max << '\n';

    return 0;
}