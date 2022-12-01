#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>

struct LLNode
{
    int64_t number;
    LLNode *previous;
    LLNode *next;

    LLNode()
        : number(0), previous(this), next(this) {}

    void add_after(int64_t n_number)
    {
        LLNode *n_next = new LLNode(n_number);

        n_next->previous = this;
        n_next->next = next;
        n_next->next->previous = n_next;

        next = n_next;
    }

    void remove_after()
    {
        LLNode *n_next = next->next;
        delete next;
        next = n_next;
        next->previous = this;
    }

private:
    LLNode(int64_t n_number)
        : number(n_number) {}
};

int main()
{
    LLNode *list = new LLNode;
    std::array<LLNode *, 1000001> where;

    {
        char c;
        std::ifstream in("input");

        while (in >> c)
        {
            list->add_after(c - '0');
            list = list->next;
            where[c - '0'] = list;
        }

        list->remove_after();

        for (int i = 10; i <= 1000000; i++)
        {
            list->add_after(i);
            list = list->next;
            where[i] = list;
        }

        list = list->next;
    }

    for (int c = 0; c < 10000000; c++) // actual slowest part
    {
        std::array<int64_t, 3> picked_up;

        for (int i = 0; i < 3; i++)
        {
            picked_up[i] = list->next->number;
            list->remove_after();
        }

        int search = list->number;

        do
        {
            search--;

            if (search < 1)
            {
                search = 1000000;
            }
        } while (std::find(picked_up.begin(), picked_up.end(), search) != std::end(picked_up));

        LLNode *destination = where[search];

        for (int i = 2; i >= 0; i--)
        {
            destination->add_after(picked_up[i]);
            where[picked_up[i]] = destination->next;
        }

        list = list->next;
    }

    list = where[1];

    int64_t answer = list->next->number * list->next->next->number;
    std::cout << answer << '\n';

    return 0;
}