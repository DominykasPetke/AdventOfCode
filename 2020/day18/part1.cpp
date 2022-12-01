#include <iostream>
#include <fstream>
#include <stack>

int main()
{
    std::string line;
    std::ifstream in("input");

    int64_t sum = 0;

    while (std::getline(in, line))
    {
        int64_t answer = 0;
        char operation = '+';

        std::stack<std::pair<int64_t, char>> stack;

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
                switch (operation)
                {
                case '*':
                    answer *= i - '0';
                    break;
                case '+':
                    answer += i - '0';
                default:
                    break;
                }
                break;
            case '+':
                operation = '+';
                break;
            case '*':
                operation = '*';
                break;
            case '(':
                stack.push({answer, operation});
                answer = 0;
                operation = '+';
                break;
            case ')':
                switch (stack.top().second)
                {
                case '+':
                    answer += stack.top().first;
                    break;
                case '*':
                    answer *= stack.top().first;
                default:
                    break;
                }

                stack.pop();
            default:
                break;
            }
        }

        sum += answer;
    }

    std::cout << sum << '\n';
    return 0;
}