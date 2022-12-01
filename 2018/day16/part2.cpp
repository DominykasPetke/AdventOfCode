#include <iostream>
#include <fstream>
#include <array>

typedef std::array<int, 4> register_set;

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

bool read(std::ifstream &in, register_set &input, register_set &opcode, register_set &out)
{
    std::string line;

    if (std::getline(in, line))
        if (line[0] == 'B')
        {
            line = line.substr(line.find('[') + 1);
            input[0] = std::stoi(line);

            line = line.substr(line.find(' ') + 1);
            input[1] = std::stoi(line);

            line = line.substr(line.find(' ') + 1);
            input[2] = std::stoi(line);

            line = line.substr(line.find(' ') + 1);
            input[3] = std::stoi(line);

            in >> opcode[0] >> opcode[1] >> opcode[2] >> opcode[3];

            in.ignore();
            std::getline(in, line);

            line = line.substr(line.find('[') + 1);
            out[0] = std::stoi(line);

            line = line.substr(line.find(' ') + 1);
            out[1] = std::stoi(line);

            line = line.substr(line.find(' ') + 1);
            out[2] = std::stoi(line);

            line = line.substr(line.find(' ') + 1);
            out[3] = std::stoi(line);

            std::getline(in, line);

            return true;
        }
        else
            return false;
    else
        return false;
}

bool read_code(std::ifstream &in, register_set &command)
{
    if (in >> command[0] >> command[1] >> command[2] >> command[3])
        return true;
    return false;
}

int main()
{
    std::array<register_set (*)(register_set const &, int, int, int), 16> funcs = {
        addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr};

    std::ifstream in("input");

    register_set init, op, out;

    std::array<register_set (*)(register_set const &, int, int, int), 16> opcodes = {
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    while (read(in, init, op, out))
    {
        int count = 0;
        int func = -1;

        for (std::size_t i = 0; i < 16; i++)
            if (funcs[i] != NULL)
                if (funcs[i](init, op[1], op[2], op[3]) == out)
                {
                    count++;
                    func = i;
                }

        if (count == 1)
        {
            opcodes[op[0]] = funcs[func];
            funcs[func] = NULL;
        }
    }

    register_set regs = {0, 0, 0, 0};
    
    while (read_code(in, op))
        regs = opcodes[op[0]](regs, op[1], op[2], op[3]);

    std::cout << regs[0] << '\n';

    return 0;
}