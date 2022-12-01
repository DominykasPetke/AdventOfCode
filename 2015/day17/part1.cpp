#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

const int target = 150;

int maths(int current_sum, size_t start_at, const std::vector<int> &sizes)
{
    int count = 0;

    if (current_sum == target)
    {
        return 1;
    }

    if (current_sum > target)
    {
        return 0;
    }

    for (size_t i = start_at; i < sizes.size(); i++)
    {
        count += maths(current_sum + sizes[i], i + 1, sizes);
    }

    return count;
}

int main()
{
    std::vector<int> sizes;

    {
        std::ifstream in("input");
        int one;

        while (in >> one)
        {
            sizes.push_back(one);
        }
    }

    std::sort(sizes.rbegin(), sizes.rend());

    int count = 0;

    for (size_t i = 0; i < sizes.size(); i++)
    {
        count += maths(sizes[i], i + 1, sizes);
    }

    std::cout << count << '\n';

    return 0;
}