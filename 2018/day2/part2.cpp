#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int compare(std::string const &a, std::string const &b)
{
    bool matched = false;
    int index = -1;

    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            if (matched) 
                return -1;
            else
            {
                matched = true;
                index = i;
            }

    return index;
}

int main()
{
    std::ifstream in("input");

    std::vector<std::string> data;

    std::string temp;

    while (in >> temp)
        data.push_back(temp);

    for (int i = 0; i < data.size(); i++)
        for (int j = i + 1; j < data.size(); j++)
            if (int index = compare(data[i], data[j]); index != -1) {
                std::cout << [index](std::string a) {a.erase(index, 1); return a; }(data[i]) << '\n';
                return 0;
            }

    std::cout << "Found nothing.\n";
    return 0;
}