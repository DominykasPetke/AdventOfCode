#include <iostream>
#include <fstream>
#include <set>
#include <numeric>
#include <queue>
#include <algorithm>

std::set<uint64_t> input_data()
{
    std::set<uint64_t> packages;
    uint64_t input;

    std::ifstream in("input");

    while (in >> input)
    {
        packages.insert(input);
    }

    return packages;
}

uint64_t multilpy(const std::set<uint64_t> &set)
{
    uint64_t ret = 1;

    for (uint64_t i : set)
    {
        ret *= i;
    }

    return ret;
}

bool equal_sums_possible(const std::set<uint64_t> &all, const std::set<uint64_t> &used, uint groups_count, uint target)
{
    if (groups_count < 1)
    {
        return false;
    }

    if (groups_count == 1)
    {
        return std::reduce(all.begin(), all.end()) - std::reduce(used.begin(), used.end()) == target;
    }

    std::set<uint64_t> remaining;

    for (uint64_t i : all)
    {
        if (!used.contains(i))
        {
            remaining.insert(i);
        }
    }

    auto sum = [](const std::set<uint64_t> &t, const std::set<uint64_t> &f) {
        return std::reduce(t.begin(), t.end()) < std::reduce(f.begin(), f.end());
    };

    // best way would be to write own priority queue that dedupes the entries
    std::priority_queue<std::set<uint64_t>, std::vector<std::set<uint64_t>>, decltype(sum)> sumqueue(sum);
    std::set<std::set<uint64_t>> dedupe_set;

    for (auto i : remaining)
    {
        std::set<uint64_t> add{i};
        sumqueue.push(add);
        //dedupe_set.insert(add);
    }

    while (!sumqueue.empty())
    {
        std::set<uint64_t> top = sumqueue.top();
        sumqueue.pop();
        //dedupe_set.erase(top);

        uint64_t top_sum = std::reduce(top.begin(), top.end());

        //std::cout << groups_count << ": " << top_sum << ' ' << top.size() << ' ' << sumqueue.size() << '\n';

        if (top_sum == target)
        {
            if (equal_sums_possible(remaining, top, groups_count - 1, target))
            {
                return true;
            }
        }

        if (top_sum < target)
        {
            for (uint64_t i : remaining)
            {
                if (top_sum + i <= target)
                {
                    std::set<uint64_t> extra = top;
                    auto ret = extra.insert(i);

                    if (ret.second && !dedupe_set.contains(extra))
                    {
                        sumqueue.push(extra);
                        dedupe_set.insert(extra);
                    }
                }
            }
        }
    }

    return false;
}

int main()
{
    std::set<uint64_t> packages = input_data();

    uint64_t sum = std::reduce(packages.begin(), packages.end());
    uint64_t target = sum / 4;

    std::set<std::set<uint64_t>> dedupe_set;

    auto f = [](const std::set<uint64_t> &t, const std::set<uint64_t> &f) {
        std::size_t t_count = t.size();
        std::size_t f_count = f.size();

        uint64_t t_mult = multilpy(t);
        uint64_t f_mult = multilpy(f);

        if (t_count == f_count)
        {
            return t_mult > f_mult;
        }

        return t_count > f_count;
    };

    std::priority_queue<std::set<uint64_t>, std::vector<std::set<uint64_t>>, decltype(f)> pqueue(f);

    for (uint64_t i : packages)
    {
        std::set<uint64_t> set{i};

        pqueue.push(set);
        //dedupe_set.insert(set);
    }

    while (!pqueue.empty())
    {
        std::set<uint64_t> top = pqueue.top();
        pqueue.pop();
        dedupe_set.erase(top);

        uint64_t top_sum = std::reduce(top.begin(), top.end());

        //std::cout << "4: " << top_sum << ' ' << top.size() << ' ' << multilpy(top) << ' ' << pqueue.size() << ' ' << dedupe_set.size() << '\n';

        if (top_sum > target) // oops, too much
        {
            continue;
        }

        if (top_sum == target) // perfection
        {
            if (equal_sums_possible(packages, top, 3, target))
            {
                std::cout << multilpy(top) << '\n';
                return 0;
            }
        }

        if (top_sum < target) // keep adding
        {
            for (uint64_t i : packages)
            {
                // IMPROVEMENT: not adding overtarget sums saves about a seocnd in runtime (it still takes half a minute anyway though)
                if (top_sum + i <= target)
                {
                    std::set<uint64_t> extra = top;
                    auto ret = extra.insert(i);

                    if (ret.second && !dedupe_set.contains(extra))
                    {
                        pqueue.push(extra);
                        dedupe_set.insert(extra);
                    }
                }
            }
        }
    }

    return 0;
}