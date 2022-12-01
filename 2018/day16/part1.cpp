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

typedef std::array<register_set (*)(register_set const &, int, int, int), 16> longboi;

int main()
{
    longboi funcs = {
        addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr};

    std::ifstream in("input");

    register_set init, op, out;

    int sum = 0;

    while (read(in, init, op, out))
    {
        int count = 0;

        for (auto f : funcs)
            if (f(init, op[1], op[2], op[3]) == out)
                count++;

        if (count >= 3)
            sum++;
    }

    std::cout << sum << '\n';

    return 0;
}