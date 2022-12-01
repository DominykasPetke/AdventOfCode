#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>

typedef std::array<int, 6> register_set;
typedef std::array<int, 4> instruction;

void addr(register_set &input, int a, int b, int c)
{
    input[c] = input[a] + input[b];
}

void addi(register_set &input, int a, int b, int c)
{
    input[c] = input[a] + b;
}

void mulr(register_set &input, int a, int b, int c)
{
    input[c] = input[a] * input[b];
}

void muli(register_set &input, int a, int b, int c)
{
    input[c] = input[a] * b;
}

void banr(register_set &input, int a, int b, int c)
{
    input[c] = input[a] & input[b];
}

void bani(register_set &input, int a, int b, int c)
{
    input[c] = input[a] & b;
}

void borr(register_set &input, int a, int b, int c)
{
    input[c] = input[a] | input[b];
}

void bori(register_set &input, int a, int b, int c)
{
    input[c] = input[a] | b;
}

void setr(register_set &input, int a, int, int c)
{
    input[c] = input[a];
}

void seti(register_set &input, int a, int, int c)
{
    input[c] = a;
}

void gtir(register_set &input, int a, int b, int c)
{
    input[c] = a > input[b];
}

void gtri(register_set &input, int a, int b, int c)
{
    input[c] = input[a] > b;
}

void gtrr(register_set &input, int a, int b, int c)
{
    input[c] = input[a] > input[b];
}

void eqir(register_set &input, int a, int b, int c)
{
    input[c] = a == input[b];
}

void eqri(register_set &input, int a, int b, int c)
{
    input[c] = input[a] == b;
}

void eqrr(register_set &input, int a, int b, int c)
{
    input[c] = input[a] == input[b];
}

int main()
{
    int instruction_pointer = 0;

    std::array<void (*)(register_set &, int, int, int), 16> funcs =
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

    register_set registers = {1, 0, 0, 0, 0, 0};

    while (registers[instruction_pointer] < (int)code.size())
    {
        funcs[code[registers[instruction_pointer]][0]](registers, code[registers[instruction_pointer]][1], code[registers[instruction_pointer]][2], code[registers[instruction_pointer]][3]);

        registers[instruction_pointer]++;
    }

    std::cout << registers[0] << '\n';

    return 0;
}