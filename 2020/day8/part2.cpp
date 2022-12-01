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

    instructions.push_back({"end", 0});

    for (std::size_t i = 0; i < instructions.size(); i++)
    {
        switch (instructions[i].first[0])
        {
        case 'j':
            instructions[i].first = "nop";
            break;
        case 'n': // acc
            instructions[i].first = "jmp";
        default:
            break;
        }

        bool been[instructions.size()];

        for (std::size_t j = 0; j < instructions.size(); j++)
        {
            been[j] = 0;
        }

        int instruction_pointer = 0;
        int accumulator = 0;

        while (!been[instruction_pointer])
        {
            been[instruction_pointer] = 1;

            switch (instructions[instruction_pointer].first[0])
            {
            case 'e':
                std::cout << accumulator << std::endl;
                return 0;
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

        switch (instructions[i].first[0]) //get it back
        {
        case 'j':
            instructions[i].first = "nop";
            break;
        case 'n': // acc
            instructions[i].first = "jmp";
        default:
            break;
        }
    }
}