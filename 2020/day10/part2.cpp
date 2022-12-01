#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// finds the next point where there is a diff of 3
uint find_next_three_diff(std::vector<uint> const &numbers, uint start)
{
    for (std::size_t i = start + 1; i < numbers.size(); i++)
    {
        if (numbers[i] - numbers[i - 1] == 3)
        {
            return i;
        }
    }

    return numbers.size() - 1;
}

// checks if the permutation is valid
bool is_valid(std::vector<uint> const &numbers)
{
    for (std::size_t i = 1; i < numbers.size(); i++)
    {
        if (numbers[i] - numbers[i - 1] > 3)
        {
            return false;
        }
    }

    return true;
}

// counts permutations
uint permutations(std::vector<uint> const &numbers, uint start, uint end)
{
    std::vector<std::vector<uint>> answers;

    answers.push_back(std::vector<uint>{numbers[start]}); // add the starting digit

    for (uint i = start + 1; i < end; i++) // make all the permutations
    {
        std::size_t size = answers.size();

        for (std::size_t j = 0; j < size; j++)
        {
            answers.push_back(std::vector<uint>(answers[j]));
            answers.back().push_back(numbers[i]);
        }
    }

    for (auto &i : answers) // add the ending digit
    {
        i.push_back(numbers[end]);
    }

    for (size_t i = 0; i < answers.size(); i++) // check validity and remove invalid
    {
        if (!is_valid(answers[i]))
        {
            answers.erase(answers.begin() + i);
            i--;
        }
    }

    return answers.size();
}

int main()
{
    std::vector<uint> numbers;

    { // input the data
        std::ifstream in("input");
        uint number;

        while (in >> number)
        {
            numbers.push_back(number);
        }
    }

    numbers.push_back(0); // add the 0 so it works nicer

    std::sort(numbers.begin(), numbers.end());

    uint64_t count = 1; // the answer counter

    for (uint curr_pos = 0; curr_pos < numbers.size() - 1;)
    {
        uint next_pos = find_next_three_diff(numbers, curr_pos);
        count *= permutations(numbers, curr_pos, next_pos);

        for (std::size_t i = curr_pos; i < next_pos; i++)
        {
            std::cout << numbers[i] << ' ';
        }

        std::cout << '\n';

        curr_pos = next_pos;
    }

    std::cout << count << '\n';
}