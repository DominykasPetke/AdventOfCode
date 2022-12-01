#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main()
{
    std::ifstream in("input");

    std::string line;

    int sum = 0;

    while (std::getline(in, line))
    {
        std::stringstream stream(line);

        std::vector<int> row;
        int temp;

        while (stream >> temp)
            row.push_back(temp);

        bool cont = true;

        for (int i = 0; i < row.size() && cont; i++)
            for (int j = i + 1; j < row.size() && cont; j++)
            {
                if (row[i] % row[j] == 0)
                {
                    sum += row[i] / row[j];
                    cont = false;
                }
                else if (row[j] % row[i] == 0)
                {
                    sum += row[j] / row[i];
                    cont = false;
                }
            }
    }

    std::cout << sum << '\n';

    return 0;
}