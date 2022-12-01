#include <iostream>
#include <array>
#include <algorithm>

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
    int best_x = -1, best_y = -1, best_size = -1;

    for (int x = 0; x < 300; x++)
        for (int y = 0; y < 300; y++)
        {
            int max_size = std::min(300 - x, 300 - y);

            for (int size = 0; size < max_size; size++)
            {
                int sum = 0;

                for (int aX = x; aX < x + size; aX++)
                    for (int aY = y; aY < y + size; aY++)
                        sum += world[aY * 300 + aX];

                if (sum > best_sum)
                {
                    best_sum = sum;
                    best_x = x + 1;
                    best_y = y + 1;
                    best_size = size;
                }
            }
        }

    std::cout << best_x << ',' << best_y << ',' << best_size << '\n';

    return 0;
}