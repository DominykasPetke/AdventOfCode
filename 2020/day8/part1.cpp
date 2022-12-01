#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("input");
    std::string instruction;
    int argument;

    std::vector<std::pair<std::string, int>> instructions;

    while (in >> instruction >> argument)
    {
        instructions.push_back({instruction, argument});
    }

    bool been[instructions.size()];

    for (std::size_t i = 0; i < instructions.size(); i++)
    {
        been[i] = 0;
    }

    int instruction_pointer = 0;
    int accumulator = 0;

    while (!been[instruction_pointer])
    {
        been[instruction_pointer] = 1;
        
        switch (instructions[instruction_pointer].first[0])
        {
        case 'j':
            instruction_pointer += instructions[instruction_pointer].second;
            break;
        case 'a': // acc
            accumulator += instructions[instruction_pointer].second;
        case 'n':
        default:
            instruction_pointer++;
            break;
        }
    }

    std::cout << accumulator << std::endl;

    return 0;
}