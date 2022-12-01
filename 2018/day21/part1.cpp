#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>

typedef std::array<long long int, 6> register_set;
typedef std::array<int, 4> instruction;

register_set addr(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] + out[b];
    return out;
}

register_set addi(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] + b;
    return out;
}

register_set mulr(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] * out[b];
    return out;
}

register_set muli(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] * b;
    return out;
}

register_set banr(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] & out[b];
    return out;
}

register_set bani(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] & b;
    return out;
}

register_set borr(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] | out[b];
    return out;
}

register_set bori(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] | b;
    return out;
}

register_set setr(register_set const &input, int a, int, int c)
{
    register_set out = input;
    out[c] = out[a];
    return out;
}

register_set seti(register_set const &input, int a, int, int c)
{
    register_set out = input;
    out[c] = a;
    return out;
}

register_set gtir(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = a > out[b];
    return out;
}

register_set gtri(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] > b;
    return out;
}

register_set gtrr(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] > out[b];
    return out;
}

register_set eqir(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = a == out[b];
    return out;
}

register_set eqri(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] == b;
    return out;
}

register_set eqrr(register_set const &input, int a, int b, int c)
{
    register_set out = input;
    out[c] = out[a] == out[b];
    return out;
}

int main()
{
    int instruction_pointer = 0;

    std::array<register_set (*)(register_set const &, int, int, int), 16> funcs =
        {addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr};

    std::vector<instruction> code;

    { // read data
        std::ifstream in("input");
        std::string line;

        std::array<std::string, 16> names =
            {"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori", "setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr"};

        while (std::getline(in, line))
            if (line[0] == '#')
                instruction_pointer = line.back() - '0';
            else
            {
                instruction ins;

                ins[0] = std::find(names.begin(), names.end(), line.substr(0, 4)) - names.begin();

                line.erase(0, line.find(' ') + 1);
                ins[1] = std::stoi(line);

                line.erase(0, line.find(' ') + 1);
                ins[2] = std::stoi(line);

                line.erase(0, line.find(' ') + 1);
                ins[3] = std::stoi(line);

                code.push_back(ins);
            }
    }

    register_set registers = {0, 0, 0, 0, 0, 0};

    while (registers[instruction_pointer] < (int)code.size())
    {
        registers = funcs[code[registers[instruction_pointer]][0]](registers, code[registers[instruction_pointer]][1], code[registers[instruction_pointer]][2], code[registers[instruction_pointer]][3]);

        registers[instruction_pointer]++;

        if (registers[instruction_pointer] == 28)
        {
            std::cout << registers[1] << '\n';
            return 0;
        }
    }

    return 0;
}