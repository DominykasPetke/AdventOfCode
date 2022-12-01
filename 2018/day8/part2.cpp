#include <iostream>
#include <fstream>
#include <vector>

int read(std::ifstream &in, int child, int meta)
{
    int sum = 0;

    if (child == 0)
        for (int i = 0; i < meta; i++)
        {
            int temp;
            in >> temp;
            sum += temp;
        }
    else
    {
        std::vector<int> nodes;

        for (int i = 0; i < child; i++)
        {
            int c, m;
            in >> c >> m;
            nodes.push_back(read(in, c, m));
        }

        for (int i = 0; i < meta; i++)
        {
            int temp;
            in >> temp;
            if (temp > 0 && temp <= child)
                sum += nodes[temp - 1];
        }
    }

    return sum;
}

int main()
{
    std::ifstream in("input");

    int child, meta;

    in >> child >> meta;

    std::cout << read(in, child, meta) << '\n';

    return 0;
}