#include <iostream>
#include <fstream>

int main()
{
    int64_t number1, number2;
    int loop2 = 0;
    std::ifstream in("input");

    in >> number1 >> number2;

    int64_t process = 1;
    do
    {
        process *= 7;
        process %= 20201227;

        loop2++;
    } while (process != number2);

    process = 1;
    for (int i = 0; i < loop2; i++)
    {
        process *= number1;
        process %= 20201227;
    }

    std::cout << process << '\n';

    return 0;
}