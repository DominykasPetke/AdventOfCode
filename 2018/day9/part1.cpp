#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct marble
{
    int score;
    marble *previous;
    marble *next;

    marble()
        : score(0), previous(this), next(this) {}

    void add_after(int n_score)
    {
        marble *n_next = new marble(n_score);

        n_next->previous = this;
        n_next->next = next;
        n_next->next->previous = n_next;

        next = n_next;
    }

    void remove_after()
    {
        marble *n_next = next->next;
        delete next;
        next = n_next;
        next->previous = this;
    }

  private:
    marble(int n_score)
        : score(n_score) {}
};

int main()
{
    int players, max_marble;

    {
        std::ifstream in("input");
        std::string temp;
        in >> players >> temp >> temp >> temp >> temp >> temp >> max_marble;
    }

    std::vector<unsigned long int> scores;
    scores.reserve(players);

    for (int i = 0; i < players; i++) // filling up player scores w/ 0s
        scores.push_back(0);

    int next_special = 23;
    int player_turn = 1;

    // setting up first marble
    marble *current_marble = new marble;

    for (int i = 1; i <= max_marble; [&i, &player_turn, players]() {
             i++;
             player_turn++;

             if (player_turn == players)
                 player_turn = 0;
         }())
        if (i == next_special) // if multiple of 23
        {
            scores[player_turn] += i;

            //move back 7 marbles
            current_marble = current_marble->previous->previous->previous->previous->previous->previous->previous;

            scores[player_turn] += current_marble->score; // add the score

            // remove the added marble
            current_marble->previous->remove_after();
            current_marble = current_marble->next;

            next_special += 23; // find next multiple of 23
        }
        else
        {
            // add marble
            current_marble->next->add_after(i);
            current_marble = current_marble->next->next; // move forward by 2, not by 1 cuz reference not moved from the line above
        }

    std::sort(scores.begin(), scores.end()); // sort points

    std::cout << scores.back() << '\n'; // print the highest one

    return 0;
}