#include <iostream>
#include <array>

#define INPUT 6392

int main()
{
    std::array<int, 300 * 300> world;

    for (int x = 0; x < 300; x++)
        for (int y = 0; y < 300; y++)
        {
            int rackID = (x + 1) + 10;
            int power_level = rackID * (y + 1);
            power_level += INPUT;
            power_level *= rackID;

            power_level = power_level / 100;
            power_level = power_level % 10;
            power_level -= 5;

            world[y * 300 + x] = power_level;
        }

    int best_sum = -9099;
    int best_x = -1, best_y = -1;
    
    for (int x = 0; x < 298; x++)
        for (int y = 0; y < 298; y++)
        {
            int sum = 0;

            sum += world[y * 300 + x];
            sum += world[y * 300 + (x + 1)];
            sum += world[y * 300 + (x + 2)];
            sum += world[(y + 1) * 300 + x];
            sum += world[(y + 1) * 300 + (x + 1)];
            sum += world[(y + 1) * 300 + (x + 2)];
            sum += world[(y + 2) * 300 + x];
            sum += world[(y + 2) * 300 + (x + 1)];
            sum += world[(y + 2) * 300 + (x + 2)];

            if (sum > best_sum)
            {
                best_sum = sum;
                best_x = x + 1;
                best_y = y + 1;
            }
        }

    std::cout << best_x << ',' << best_y << '\n';

    return 0;
}