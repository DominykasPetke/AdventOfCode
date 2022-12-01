#include <fstream>
#include <iostream>

int main()
{
    std::ifstream in("input");

    int number;
    int ans = 0;

    while (in >> number) 
        ans += number;

    std::cout << ans << '\n';

    return 0;
}