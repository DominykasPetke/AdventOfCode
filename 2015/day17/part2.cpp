#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

const int target = 150;

void maths(int current_sum, size_t start_at, const std::vector<int> &sizes, int layer, std::vector<int> &counts)
{
    if (current_sum == target)
    {
        counts.push_back(layer);
        return;
    }

    if (current_sum > target)
    {
        return;
    }

    for (size_t i = start_at; i < sizes.size(); i++)
    {
        maths(current_sum + sizes[i], i + 1, sizes, layer + 1, counts);
    }
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

    std::vector<int> counts;

    for (size_t i = 0; i < sizes.size(); i++)
    {
        maths(sizes[i], i + 1, sizes, 1, counts);
    }

    std::cout << std::count(counts.begin(), counts.end(), *(std::min_element(counts.begin(), counts.end()))) << '\n';

    return 0;
}