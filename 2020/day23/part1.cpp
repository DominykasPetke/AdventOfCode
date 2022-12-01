#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>

struct LLNode
{
    int number;
    LLNode *previous;
    LLNode *next;

    LLNode()
        : number(0), previous(this), next(this) {}

    void add_after(int n_number)
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
    LLNode(int n_number)
        : number(n_number) {}
};

int main()
{
    LLNode *list = new LLNode;

    {
        char c;
        std::ifstream in("input");

        while (in >> c)
        {
            list->add_after(c - '0');
            list = list->next;
        }

        list->remove_after();
        list = list->next;
    }

    for (int c = 0; c < 100; c++)
    {
        std::array<int, 3> picked_up;

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
                search = 9;
            }
        } while (std::find(picked_up.begin(), picked_up.end(), search) != std::end(picked_up));

        LLNode *destination = list;

        while (destination->number != search)
        {
            destination = destination->next;
        }

        for (int i = 2; i >= 0; i--)
        {
            destination->add_after(picked_up[i]);
        }

        list = list->next;
    }

    while (list->number != 1)
    {
        list = list->next;
    }

    list = list->next;

    while (list->number != 1)
    {
        std::cout << list->number;
        list = list->next;
    }

    std::cout << '\n';

    return 0;
}