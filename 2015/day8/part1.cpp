#include <iostream>
#include <fstream>

int main()
{
    std::ifstream in("input");
    std::string line;

    int answer = 0;
    while (std::getline(in, line))
    {
        answer += 2;

        size_t pos = 0;

        while ((pos = line.find(92)) != std::string::npos)
        {
            line.erase(0, pos + 1);

            if (line.length() > 0)
                switch (line[0])
                {
                case 92:
                    line.erase(0, 1);
                case '"':
                    answer++;
                    break;

                case 'x':
                    if (isxdigit(line[1]) && isxdigit(line[2]))
                        answer += 3;
                default:
                    break;
                }
        }
    }

    std::cout << answer << '\n';

    return 0;
}