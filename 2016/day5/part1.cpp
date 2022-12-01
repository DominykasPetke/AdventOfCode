#include <iostream>
#include <fstream>
#include <string>

// MD5 code taken from https://github.com/azureatom/md5
#include "md5.h"

int main()
{
    std::ifstream in("input");
    std::string line;

    in >> line;

    for (int i = 0, counter = 0; i < 8; counter++)
    {
        std::string to_hash = line + std::to_string(counter);

        std::string out = md5sum(to_hash.c_str(), to_hash.length());

        if (out.starts_with("00000"))
        {
            i++;
            std::cout << out[5];
        }
    }

    std::cout << '\n';

    return 0;
}