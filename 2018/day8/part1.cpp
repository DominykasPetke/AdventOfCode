#include <iostream>
#include <fstream>

int read(std::ifstream &in, int child, int meta)
{
    int sum = 0;

    for (int i = 0; i < child; i++)
    {
        int c, m;
        in >> c >> m;
        sum += read(in, c, m);
    }

    for (int i = 0; i < meta; i++)
    {
        int temp;
        in >> temp;
        sum += temp;
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