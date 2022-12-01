#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

bool isSum(int64_t number, std::vector<int64_t> numbers)
{
    for (int i = 0; i < 25; i++)
    {
        for (int j = i; j < 25; j++)
        {
            if (numbers[i] + numbers[j] == number)
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    std::ifstream in("input");
    int64_t number;

    {
        std::vector<int64_t> numbers;

        for (int i = 0; i < 25; i++)
        {
            in >> number;
            numbers.push_back(number);
        }

        while (in >> number)
        {
            if (!isSum(number, numbers))
            {
                std::cout << "Part 1: " << number << '\n';
                break;
            }

            numbers.erase(numbers.begin());
            numbers.push_back(number);
        }
    }

    in.seekg(0);

    int64_t sum = 0;
    int64_t input;
    std::vector<int64_t> array;

    while (in >> input)
    {
        sum += input;
        array.push_back(input);

        if (sum == number)
        {
            std::cout << "Part 2: " << *std::max_element(array.begin(), array.end()) + *std::min_element(array.begin(), array.end()) << '\n';
            return 0;
        }

        while (sum > number)
        {
            sum -= array[0];
            array.erase(array.begin());
        }
    }
}