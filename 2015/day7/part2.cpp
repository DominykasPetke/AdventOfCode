#include <iostream>
#include <fstream>
#include <map>
#include <vector>

class Wire
{
    uint16_t Value;
    std::string Op1;
    char Code;
    std::string Op2;
    bool HasValue;
    static std::map<std::string, Wire> circuit_copy;

public:
    static std::map<std::string, Wire> circuit;

    Wire(uint16_t value)
    {
        Value = value;
        HasValue = true;
    }

    Wire(std::string op1, std::string op2, char code)
    {
        Op1 = op1;
        Op2 = op2;
        Code = code;
        HasValue = false;
    }

    Wire(std::string op1, char code)
    {
        Op1 = op1;
        Code = code;
        HasValue = false;
    }

    Wire()
    {
    }

    uint16_t GetValue()
    {
        if (HasValue)
            return Value;

        uint16_t op1;
        uint16_t op2;

        switch (Code)
        {
        case '|':
            try
            {
                op1 = std::stoi(Op1);
                op2 = circuit[Op2].GetValue();

                Value = op1 | op2;
                HasValue = true;

                return Value;
            }
            catch (...)
            {
                try
                {
                    op2 = std::stoi(Op2);
                    op1 = circuit[Op1].GetValue();

                    Value = op1 | op2;
                    HasValue = true;

                    return Value;
                }
                catch (...)
                {
                    op1 = circuit[Op1].GetValue();
                    op2 = circuit[Op2].GetValue();

                    Value = op1 | op2;
                    HasValue = true;

                    return Value;
                }
            }
            break;
        case '=':
            Value = circuit[Op1].GetValue();
            HasValue = true;

            return Value;
            break;
        case '&':
            try
            {
                op1 = std::stoi(Op1);
                op2 = circuit[Op2].GetValue();

                Value = op1 & op2;
                HasValue = true;

                return Value;
            }
            catch (...)
            {
                try
                {
                    op2 = std::stoi(Op2);
                    op1 = circuit[Op1].GetValue();

                    Value = op1 & op2;
                    HasValue = true;

                    return Value;
                }
                catch (...)
                {
                    op1 = circuit[Op1].GetValue();
                    op2 = circuit[Op2].GetValue();

                    Value = op1 & op2;
                    HasValue = true;

                    return Value;
                }
            }
            break;
        case '>':
            op1 = circuit[Op1].GetValue();

            Value = op1 >> std::stoi(Op2);
            HasValue = true;

            return Value;
            break;
        case '<':
            op1 = circuit[Op1].GetValue();

            Value = op1 << std::stoi(Op2);
            HasValue = true;

            return Value;
            break;
        case '!':
            op1 = circuit[Op1].GetValue();

            Value = ~op1;
            HasValue = true;

            return Value;
        default:
            break;
        }
        return 0;
    }

    static void SaveCopy()
    {
        circuit_copy = circuit;
    }

    static void RestoreCopy()
    {
        circuit = circuit_copy;
    }
};

std::map<std::string, Wire> Wire::circuit;
std::map<std::string, Wire> Wire::circuit_copy;

std::vector<std::string> splitString(std::string line)
{
    size_t pos = 0;
    std::string token;

    std::vector<std::string> ret;

    while ((pos = line.find(' ')) != std::string::npos)
    {
        token = line.substr(0, pos);
        ret.push_back(token);
        line.erase(0, pos + 1);
    }

    ret.push_back(line);

    return ret;
}

int main()
{
    std::ifstream in("input");
    std::string line;

    while (std::getline(in, line))
    {
        std::vector<std::string> split = splitString(line);

        switch (split.size())
        {
        case 3: // only direct assignments
            try
            {
                uint16_t value = std::stoi(split[0]);
                Wire::circuit[split[2]] = {value};
            }
            catch (...)
            {
                Wire::circuit[split[2]] = {split[0], '='};
            }
            break;
        case 4: // only NOTs
            Wire::circuit[split[3]] = {split[1], '!'};
            break;
        case 5: // everything else
            switch (split[1][0])
            {
            case 'O':
                Wire::circuit[split[4]] = {split[0], split[2], '|'};
                break;
            case 'A':
                Wire::circuit[split[4]] = {split[0], split[2], '&'};
                break;
            case 'L':
                Wire::circuit[split[4]] = {split[0], split[2], '<'};
                break;
            case 'R':
                Wire::circuit[split[4]] = {split[0], split[2], '>'};
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    Wire::SaveCopy();

    uint16_t ats = Wire::circuit["a"].GetValue();

    Wire::RestoreCopy();
    Wire::circuit["b"] = {ats};

    ats = Wire::circuit["a"].GetValue();
    std::cout << ats << '\n';

    return 0;
}