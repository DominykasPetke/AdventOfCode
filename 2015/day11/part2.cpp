#include <iostream>
#include <fstream>
#include <algorithm>

bool valid(const std::string &pass)
{
    if (std::find(pass.begin(), pass.end(), 'i') != pass.end() &&
        std::find(pass.begin(), pass.end(), 'o') != pass.end() &&
        std::find(pass.begin(), pass.end(), 'l') != pass.end())
    {
        return false;
    }

    bool increasing = false;

    for (size_t i = 0; i < pass.size() - 2 && !increasing; i++)
    {
        if (pass[i] + 2 == pass[i + 2] && pass[i + 1] + 1 == pass[i + 2])
        {
            increasing = true;
        }
    }

    bool pair = false;
    bool pairs = false;

    for (size_t i = 0; i < pass.size() - 1 && !pairs; i++)
    {
        if (pass[i] == pass[i + 1])
        {
            if (!pair)
            {
                pair = true;
                i++;
            }
            else
            {
                pairs = true;
                i++;
            }
        }
    }

    return increasing && pairs;
}

std::string increment(std::string pass)
{
    size_t last = pass.size() - 1;

    bool done = false;

    while (!done)
    {
        if (pass[last] != 'z')
        {
            pass[last]++;
            done = true;
        }
        else
        {
            pass[last] = 'a';
            last--;
        }
    }

    return pass;
}

int main()
{
    std::string password;

    {
        std::ifstream in("input");
        in >> password;
    }

    while (!valid(password))
    {
        password = increment(password);
    }

    password = increment(password);

    while (!valid(password))
    {
        password = increment(password);
    }

    std::cout << password << '\n';

    return 0;
}