#include <iostream>
#include <fstream>

int main()
{
    std::ifstream in("input");
    int max = 0;
    std::string line;

    while (std::getline(in, line))
    {
        int id = 0;

        for (char c : line)
        {
            switch (c)
            {
            case 'F':
            case 'L':
                id = id << 1;
                id = id | 0;
                break;
            case 'B':
            case 'R':
                id = id << 1;
                id = id | 1;
                break;
            default:
                break;
            }
        }

        if (id > max)
        {
            max = id;
        }
    }

    std::cout << max << std::endl;

    return 0;
}