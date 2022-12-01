#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <sstream>

std::size_t replace_all(std::string &inout, std::string const &what, std::string const &with)
{
    std::size_t count{};

    for (std::string::size_type pos{};
         inout.npos != (pos = inout.find(what.data(), pos, what.length()));
         pos += with.length(), ++count)
    {
        inout.replace(pos, what.length(), with.data(), with.length());
    }

    return count;
}

bool bingo(std::array<std::array<std::pair<int, bool>, 5>, 5> const &table, unsigned int number, bool row)
{
    if (row)
    {
        for (unsigned int i = 0; i < 5; i++)
        {
            if (!table[number][i].second)
            {
                return false;
            }
        }

        return true;
    }
    else
    {
        for (unsigned int i = 0; i < 5; i++)
        {
            if (!table[i][number].second)
            {
                return false;
            }
        }

        return true;
    }
}

bool check_board(std::array<std::array<std::pair<int, bool>, 5>, 5> const &table)
{
    for (unsigned int i = 0; i < 5; i++)
    {
        if (bingo(table, i, false))
        {
            return true;
        }

        if (bingo(table, i, true))
        {
            return true;
        }
    }

    return false;
}

int main()
{
    std::string bingo_numbers;
    std::vector<std::array<std::array<std::pair<int, bool>, 5>, 5>> tables;

    {
        std::ifstream in("input");
        in >> bingo_numbers;

        replace_all(bingo_numbers, ",", " ");

        std::array<std::pair<int, bool>, 5> line;
        std::array<std::array<std::pair<int, bool>, 5>, 5> table;
        unsigned int i = 0;

        while (in >> line[0].first >> line[1].first >> line[2].first >> line[3].first >> line[4].first)
        {
            line[0].second = false;
            line[1].second = false;
            line[2].second = false;
            line[3].second = false;
            line[4].second = false;

            table[i] = line;

            i += 1;
            i %= 5;

            if (i == 0)
            {
                tables.push_back(table);
            }
        }
    }

    std::stringstream numbers(bingo_numbers);

    int number;
    while (numbers >> number)
    {
        for (auto &t : tables)
        {
            for (auto &r : t)
            {
                for (auto &c : r)
                {
                    if (c.first == number)
                    {
                        c.second = true;

                        if (check_board(t))
                        {
                            int sum = 0;

                            for (auto r2 : t)
                            {
                                for (auto c2 : r2)
                                {
                                    if (!c2.second)
                                    {
                                        sum += c2.first;
                                    }
                                }
                            }

                            std::cout << sum * number << '\n';
                            return 0;
                        }
                    }
                }
            }
        }
    }

    std::cout << "FAILED" << '\n';

    return 0;
}