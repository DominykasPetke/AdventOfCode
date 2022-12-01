#include <iostream>
#include <fstream>
#include <vector>
#include <array>

int main()
{
    std::string line;
    std::vector<std::string> oxygen;
    std::vector<std::string> carbon;

    std::ifstream in("input");
    in >> line;

    do
    {
        oxygen.push_back(line);
        carbon.push_back(line);
    } while (in >> line);

    for (unsigned int c = 0; c < line.size(); c++)
    {
        if (oxygen.size() > 1)
        {
            std::array<int, 2> data = {0, 0};

            for (unsigned int i = 0; i < oxygen.size(); i++)
            {
                switch (oxygen[i][c])
                {
                case '0':
                    data[0]++;
                    break;
                case '1':
                    data[1]++;

                default:
                    break;
                }
            }

            for (unsigned int i = 0; i < oxygen.size(); i++)
            {
                if (data[0] > data[1])
                {
                    if (oxygen[i][c] == '1')
                    {
                        oxygen.erase(oxygen.begin() + i);
                        i--;
                    }
                }
                else
                {
                    if (oxygen[i][c] == '0')
                    {
                        oxygen.erase(oxygen.begin() + i);
                        i--;
                    }
                }

                if (oxygen.size() == 1)
                {
                    break;
                }
            }
        }

        if (carbon.size() > 1)
        {
            std::array<int, 2> data = {0, 0};

            for (unsigned int i = 0; i < carbon.size(); i++)
            {
                switch (carbon[i][c])
                {
                case '0':
                    data[0]++;
                    break;
                case '1':
                    data[1]++;

                default:
                    break;
                }
            }

            for (unsigned int i = 0; i < carbon.size(); i++)
            {
                if (data[1] >= data[0])
                {
                    if (carbon[i][c] == '1')
                    {
                        carbon.erase(carbon.begin() + i);
                        i--;
                    }
                }
                else
                {
                    if (carbon[i][c] == '0')
                    {
                        carbon.erase(carbon.begin() + i);
                        i--;
                    }
                }

                if (carbon.size() == 1)
                {
                    break;
                }
            }
        }
    }

    int oxy_num = std::stoi(oxygen[0], nullptr, 2);
    int car_num = std::stoi(carbon[0], nullptr, 2);

    std::cout << oxy_num * car_num << '\n';

    return 0;
}