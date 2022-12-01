#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream in("input");
    std::string line;

    std::vector<int> IDs;

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

        IDs.push_back(id);
    }

    std::sort(IDs.begin(), IDs.end());

    for (int i = *(IDs.begin()); i < *(IDs.end() - 1); i++)
    {
        if (std::find(IDs.begin(), IDs.end(), i) == std::end(IDs))
        {
            std::cout << i << '\n';
        }
    }

    return 0;
}