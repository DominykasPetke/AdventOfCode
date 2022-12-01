#include <iostream>
#include <fstream>
#include <queue>

int main()
{
    std::ifstream in("input");

    int prev = 0;
    int sum = 0;
    std::queue<int> q;
    int number;
    int increases = 0;

    in >> number;
    sum += number;
    q.push(number);
    
    in >> number;
    sum += number;
    q.push(number);

    while (in >> number)
    {
        sum += number;
        q.push(number);

        if (prev == 0)
        {
            prev = sum;
        }

        if (prev < sum)
        {
            increases++;
        }

        prev = sum;
        sum -= q.front();
        q.pop();
    }

    std::cout << increases << '\n';

    return 0;
}