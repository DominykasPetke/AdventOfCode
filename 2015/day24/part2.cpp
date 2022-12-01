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
        dedupe_set.insert(set);
    }

    while (!pqueue.empty())
    {
        std::set<uint64_t> top = pqueue.top();
        pqueue.pop();
        dedupe_set.erase(top);

        uint64_t top_sum = std::reduce(top.begin(), top.end());

        //std::cout << "1: " << top_sum << ' ' << top.size() << ' ' << multilpy(top) << ' ' << pqueue.size() << ' ' << dedupe_set.size() << '\n';

        if (top_sum > target) // oops, too much
        {
            continue;
        }

        if (top_sum == target) // perfection
        {
            std::set<uint64_t> remaining;

            for (uint64_t i : packages)
            {
                if (!top.contains(i))
                {
                    remaining.insert(i);
                }
            }

            auto sum = [](const std::set<uint64_t> &t, const std::set<uint64_t> &f) {
                return std::reduce(t.begin(), t.end()) < std::reduce(f.begin(), f.end());
            };

            std::priority_queue<std::set<uint64_t>, std::vector<std::set<uint64_t>>, decltype(sum)> sumqueue(sum);
            std::set<std::set<uint64_t>> dedupe_sum;

            for (auto i : remaining)
            {
                std::set<uint64_t> add{i};
                sumqueue.push(add);
                dedupe_sum.insert(add);
            }

            while (!sumqueue.empty())
            {
                std::set<uint64_t> rem = sumqueue.top();
                sumqueue.pop();
                dedupe_sum.erase(rem);

                uint64_t rem_sum = std::reduce(rem.begin(), rem.end());

                //std::cout << "2: " << rem_sum << ' ' << rem.size() << ' ' << sumqueue.size() << '\n';

                if (rem_sum > target)
                {
                    continue;
                }

                if (rem_sum == target)
                {
                    std::set<uint64_t> remaining2;

                    for (uint64_t i : remaining)
                    {
                        if (!rem.contains(i))
                        {
                            remaining2.insert(i);
                        }
                    }

                    std::priority_queue<std::set<uint64_t>, std::vector<std::set<uint64_t>>, decltype(sum)> sumqueue2(sum);
                    std::set<std::set<uint64_t>> dedupe_sum2;

                    for (auto i : remaining2)
                    {
                        std::set<uint64_t> add{i};
                        sumqueue2.push(add);
                        dedupe_sum2.insert(add);
                    }

                    while (!sumqueue2.empty())
                    {
                        std::set<uint64_t> rem2 = sumqueue2.top();
                        sumqueue2.pop();
                        dedupe_sum2.erase(rem);

                        uint64_t rem_sum2 = std::reduce(rem2.begin(), rem2.end());

                        //std::cout << "3: " << rem_sum2 << ' ' << rem2.size() << ' ' << sumqueue2.size() << '\n';

                        if (rem_sum2 > target)
                        {
                            continue;
                        }

                        if (rem_sum2 == target)
                        {
                            std::cout << multilpy(top) << '\n';
                            return 0;
                        }

                        if (rem_sum2 < target)
                        {
                            for (uint64_t i : remaining2)
                            {
                                std::set<uint64_t> extra = rem2;
                                auto ret = extra.insert(i);

                                if (ret.second && !dedupe_sum2.contains(extra))
                                {
                                    sumqueue2.push(extra);
                                    dedupe_sum2.insert(extra);
                                }
                            }
                        }
                    }
                }

                if (rem_sum < target)
                {
                    for (uint64_t i : remaining)
                    {
                        std::set<uint64_t> extra = rem;
                        auto ret = extra.insert(i);

                        if (ret.second && !dedupe_sum.contains(extra))
                        {
                            sumqueue.push(extra);
                            dedupe_sum.insert(extra);
                        }
                    }
                }
            }
        }

        if (top_sum < target) // keep adding
        {
            for (uint64_t i : packages)
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

    return 0;
}