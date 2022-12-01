#include <iostream>
#include <fstream>
#include <stack>

int main()
{
    std::string line;
    std::ifstream in("input");

    int64_t result = 0;

    while (std::getline(in, line))
    {
        int64_t answer = 1;
        int64_t sum = 0;

        std::stack<std::pair<int64_t, int64_t>> stack;

        for (char i : line)
        {
            switch (i)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                sum += i - '0';
                break;
            case '*':
                answer *= sum;
                sum = 0;
                break;
            case '(':
                stack.push({answer, sum});

                answer = 1;
                sum = 0;
                break;
            case ')':
                sum *= answer;
                sum += stack.top().second;
                answer = stack.top().first;
                stack.pop();
            default:
                break;
            }
        }

        answer *= sum;
        result += answer;
    }

    std::cout << result << '\n';
    return 0;
}