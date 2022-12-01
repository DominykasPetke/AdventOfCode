#include <iostream>
#include <fstream>

int main()
{
    std::ifstream in("input");
    std::string line;

    int answer = 0;
    while (std::getline(in, line))
    {
        answer += 2;
        
        for (char c : line)
            if (c == '"' || c == '\\')
                answer++;
    }

    std::cout << answer << '\n';

    return 0;
}