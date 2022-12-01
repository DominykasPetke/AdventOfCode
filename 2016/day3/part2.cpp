#include <iostream>
#include <fstream>
#include <vector>

void loop(std::vector<int> const & data, int & sum)
{
    for (int i = 0; i < data.size(); i += 3) 
        if (data[i] + data[i + 1] > data[i + 2] && data[i] + data[i + 2] > data[i + 1] && data[i + 1] + data[i + 2] > data[i])
            sum++;
}

int main()
{
    std::ifstream in("input");
    int sum = 0;
    std::vector<int> one, two, three;

    while (!in.eof())
    {
        int a, b, c;
        in >> a >> b >> c;

        one.push_back(a);
        two.push_back(b);
        three.push_back(c);
    }

    loop(one, sum);
    loop(two, sum);
    loop(three, sum);

    std::cout << sum << '\n';

    return 0;
}