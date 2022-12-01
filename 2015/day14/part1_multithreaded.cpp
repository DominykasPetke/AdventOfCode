#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

class Reindeer
{
    std::string name_;
    long unsigned int speed_;
    long unsigned int time_;
    long unsigned int rest_time_;

    bool resting_;
    unsigned int remaining_;

public:
    unsigned int distance_;

    Reindeer(std::string name, long unsigned int speed, long unsigned int time, long unsigned int rest_time)
        : name_(name), speed_(speed), time_(time), rest_time_(rest_time), resting_(false), remaining_(time), distance_(0) {}

    void simulate()
    {
        for (int i = 0; i < 2503; i++)
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

            deers.push_back({values[0], std::stoul(values[3]), std::stoul(values[6]), std::stoul(values[13])});
        }
    }

    std::vector<std::thread> threads;

    for (auto &r : deers)
    {
        threads.push_back(std::thread(&Reindeer::simulate, &r));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    unsigned int max = 0;

    for (auto i : deers)
    {
        if (i.distance_ > max)
        {
            max = i.distance_;
        }
    }

    std::cout << max << '\n';

    return 0;
}