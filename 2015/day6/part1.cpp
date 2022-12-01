#include <fstream>
#include <iostream>
#include <array>

int main()
{
    std::ifstream in("input");

    std::array<std::array<bool, 1000>, 1000> lights;

    for (int x = 0; x < 1000; x++)
    {
        for (int y = 0; y < 1000; y++)
        {
            lights[x][y] = false;
        }
    }

    while (!in.eof())
    {
        std::string line;
        std::getline(in, line);

        if (line.length() > 10)
        {
            int start_x, start_y, end_x, end_y, x_l, y_l, ex_l;

            switch (line[6])
            {
            case ' ': // toggle
                start_x = std::stoi(line.substr(7, 3));
                x_l = std::to_string(start_x).length();
                start_y = std::stoi(line.substr(8 + x_l, 3));
                y_l = std::to_string(start_y).length();
                end_x = std::stoi(line.substr(17 + x_l + y_l, 3));
                ex_l = std::to_string(end_x).length();
                end_y = std::stoi(line.substr(18 + x_l + y_l + ex_l, 3));

                for (int x = start_x; x <= end_x; x++)
                {
                    for (int y = start_y; y <= end_y; y++)
                    {
                        lights[x][y] = !lights[x][y];
                    }
                }

                break;

            case 'n': // turn on
                start_x = std::stoi(line.substr(8, 3));
                x_l = std::to_string(start_x).length();
                start_y = std::stoi(line.substr(9 + x_l, 3));
                y_l = std::to_string(start_y).length();
                end_x = std::stoi(line.substr(18 + x_l + y_l, 3));
                ex_l = std::to_string(end_x).length();
                end_y = std::stoi(line.substr(19 + x_l + y_l + ex_l, 3));

                for (int x = start_x; x <= end_x; x++)
                {
                    for (int y = start_y; y <= end_y; y++)
                    {
                        lights[x][y] = true;
                    }
                }
                break;

            case 'f': // turn off
                start_x = std::stoi(line.substr(9, 3));
                x_l = std::to_string(start_x).length();
                start_y = std::stoi(line.substr(10 + x_l, 3));
                y_l = std::to_string(start_y).length();
                end_x = std::stoi(line.substr(19 + x_l + y_l, 3));
                ex_l = std::to_string(end_x).length();
                end_y = std::stoi(line.substr(20 + x_l + y_l + ex_l, 3));

                for (int x = start_x; x <= end_x; x++)
                {
                    for (int y = start_y; y <= end_y; y++)
                    {
                        lights[x][y] = false;
                    }
                }
                break;

            default:
                break;
            }
        }
    }

    int sum = 0;
    for (int x = 0; x < 1000; x++)
    {
        for (int y = 0; y < 1000; y++)
        {
            sum += lights[x][y];
        }
    }

    std::cout << sum << '\n';

    return 0;
}