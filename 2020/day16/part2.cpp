#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <unordered_map>

struct Field
{
    int lowmin;
    int lowmax;
    int himin;
    int himax;

    bool valid(int number)
    {
        return (number >= lowmin && number <= lowmax) || (number >= himin && number <= himax);
    }
};

int main()
{

    std::vector<Field> fields;
    std::vector<int> departures;
    std::vector<std::vector<int>> valid_tickets;
    std::vector<int> my_ticket;

    {
        std::string line;
        std::ifstream in("input");

        while (std::getline(in, line)) // first part
        {
            std::smatch match;

            if (!std::regex_search(line, match, std::regex("(\\d+)-(\\d+) or (\\d+)-(\\d+)")))
            {
                std::getline(in, line);
                std::getline(in, line);

                break;
            }

            if (line.starts_with("departure"))
            {
                departures.push_back(fields.size());
            }

            fields.push_back({std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4])});
        }

        int number;

        std::stringstream ss(std::regex_replace(line, std::regex(","), " "));

        while (ss >> number)
        {
            my_ticket.push_back(number);
        }

        std::getline(in, line);
        std::getline(in, line);

        while (std::getline(in, line)) // filter tickets
        {
            std::stringstream ss(std::regex_replace(line, std::regex(","), " "));

            std::vector<int> ticket;

            if ([&ss, &fields, &number, &ticket]() {
                    while (ss >> number)
                    {
                        if (![&fields, number, &ticket]() {
                                for (auto i : fields)
                                {
                                    if (i.valid(number))
                                    {
                                        ticket.push_back(number);
                                        return true;
                                    }
                                }

                                return false;
                            }())
                        {
                            return false;
                        }
                    }

                    return true;
                }())
            {
                valid_tickets.push_back(ticket);
            }
        }
    }

    std::unordered_map<int, int> positions;
    std::unordered_map<int, std::vector<int>> possibilities;

    for (std::size_t i = 0; i < fields.size(); i++) // find out which positions can be valid
    {
        possibilities[i] = [&valid_tickets, &positions](Field field) {
            std::vector<int> possible;

            for (std::size_t i = 0; i < valid_tickets.front().size(); i++)
            {
                if ([valid_tickets, &field, i]() {
                        for (auto t : valid_tickets)
                        {
                            if (!field.valid(t[i]))
                            {
                                return false;
                            }
                        }

                        return true;
                    }())
                {
                    possible.push_back(i);
                }
            }

            return possible;
        }(fields[i]);
    }

    std::size_t count = 0;

    while (count < fields.size()) // until we figure out all positions
    {
        for (std::size_t i = 0; i < possibilities.size(); i++) 
        {
            if (possibilities[i].size() == 1) // if there's only one valid place
            {
                positions[i] = possibilities[i][0]; // it is there
                count++;

                for (std::size_t p = 0; p < possibilities.size(); p++) // remove mentions of it elsewhere
                {
                    for (std::size_t x = 0; x < possibilities[p].size(); x++)
                    {
                        if (possibilities[p][x] == positions[i])
                        {
                            possibilities[p].erase(possibilities[p].begin() + x);
                        }
                    }
                }
            }
        }
    }

    int64_t ans = 1;

    for (auto i : departures)
    {
        ans *= my_ticket[positions[i]];
    }

    std::cout << ans << '\n';

    return 0;
}