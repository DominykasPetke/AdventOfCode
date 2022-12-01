#include <iostream>
#include <fstream>
#include <vector>

struct FCall
{
    void (*function_to_call)(uint *, const int, uint *);
    uint *reg;
    int offset;
    uint *ip;

    void call()
    {
        function_to_call(reg, offset, ip);
    }
};

void hlf(uint *reg, const int, uint *)
{
    (*reg) /= 2;
}

void tpl(uint *reg, const int, uint *)
{
    (*reg) *= 3;
}

void inc(uint *reg, const int, uint *i)
{
    (*reg)++;
}

void jmp(uint *, const int offset, uint *ip)
{
    (*ip) += offset;
    (*ip)--;
}

void jie(uint *reg, const int offset, uint *ip)
{
    if ((*reg) % 2 == 0)
    {
        (*ip) += offset;
        (*ip)--;
    }
}

void jio(uint *reg, const int offset, uint *ip)
{
    if ((*reg) == 1)
    {
        (*ip) += offset;
        (*ip)--;
    }
}

int main()
{
    uint a = 0, b = 0;
    uint instruction_pointer = 0;
    std::vector<FCall> calls;

    {
        std::ifstream in("input");
        std::string line;

        while (std::getline(in, line))
        {
            switch (line[2])
            {
            case 'f':
                calls.push_back({hlf, line[4] == 'a' ? &a : &b, 0, &instruction_pointer});
                break;
            case 'l':
                calls.push_back({tpl, line[4] == 'a' ? &a : &b, 0, &instruction_pointer});
                break;
            case 'c':
                calls.push_back({inc, line[4] == 'a' ? &a : &b, 0, &instruction_pointer});
                break;
            case 'p':
                calls.push_back({jmp, &a, std::stoi(line.substr(4)), &instruction_pointer});
                break;
            case 'e':
                calls.push_back({jie, line[4] == 'a' ? &a : &b, std::stoi(line.substr(7)), &instruction_pointer});
                break;
            case 'o':
                calls.push_back({jio, line[4] == 'a' ? &a : &b, std::stoi(line.substr(7)), &instruction_pointer});
                break;

            default:
                break;
            }
        }
    }

    while (instruction_pointer < calls.size())
    {
        calls[instruction_pointer].call();
        instruction_pointer++;
    }

    std::cout << b << '\n';

    return 0;
}