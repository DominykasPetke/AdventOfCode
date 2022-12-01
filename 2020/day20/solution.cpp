#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <queue>

struct Tile
{
    int number;
    std::vector<std::vector<bool>> image;

    void flip_upside_down()
    {
        std::vector<std::vector<bool>> new_tile;

        for (auto i = image.rbegin(); i != image.rend(); i++)
        {
            new_tile.push_back(*i);
        }

        image = new_tile;
    }

    void flip_left_right()
    {
        std::vector<std::vector<bool>> new_tile;

        for (auto const i : image)
        {
            std::vector<bool> line;

            for (auto c = i.rbegin(); c != i.rend(); c++)
            {
                line.push_back(*c);
            }

            new_tile.push_back(line);
        }

        image = new_tile;
    }

    void flip_both()
    {
        std::vector<std::vector<bool>> new_tile;

        for (auto i = image.rbegin(); i != image.rend(); i++)
        {
            std::vector<bool> line;

            for (auto c = (*i).rbegin(); c != (*i).rend(); c++)
            {
                line.push_back(*c);
            }

            new_tile.push_back(line);
        }

        image = new_tile;
    }

    void rotate()
    {
        std::vector<std::vector<bool>> new_tile;

        for (std::size_t i = 0; i < image.size(); i++)
        {
            std::vector<bool> line;

            for (auto j = image.rbegin(); j != image.rend(); j++)
            {

                line.push_back((*j)[i]);
            }

            new_tile.push_back(line);
        }

        image = new_tile;
    }

    void remove_borders()
    {
        std::vector<std::vector<bool>> new_tile;

        for (auto i = image.begin() + 1; i != image.end() - 1; i++)
        {
            std::vector<bool> line;

            for (auto j = (*i).begin() + 1; j != (*i).end() - 1; j++)
            {
                line.push_back(*j);
            }

            new_tile.push_back(line);
        }

        image = new_tile;
    }

    std::vector<bool> get_top() const
    {
        return image.front();
    }

    std::vector<bool> get_bottom() const
    {
        return image.back();
    }

    std::vector<bool> get_top_flipped() const
    {
        std::vector<bool> flip;

        for (auto i = image.front().rbegin(); i != image.front().rend(); i++)
        {
            flip.push_back(*i);
        }

        return flip;
    }

    std::vector<bool> get_bottom_flipped() const
    {
        std::vector<bool> flip;

        for (auto i = image.back().rbegin(); i != image.back().rend(); i++)
        {
            flip.push_back(*i);
        }

        return flip;
    }

    std::vector<bool> get_left() const
    {
        std::vector<bool> ret;

        for (auto const i : image)
        {
            ret.push_back(i.front());
        }

        return ret;
    }

    std::vector<bool> get_right() const
    {
        std::vector<bool> ret;

        for (auto const i : image)
        {
            ret.push_back(i.back());
        }

        return ret;
    }

    std::vector<bool> get_left_flipped() const
    {
        std::vector<bool> ret;

        for (auto i = image.rbegin(); i != image.rend(); i++)
        {
            ret.push_back((*i).front());
        }

        return ret;
    }

    std::vector<bool> get_right_flipped() const
    {
        std::vector<bool> ret;

        for (auto i = image.rbegin(); i != image.rend(); i++)
        {
            ret.push_back((*i).back());
        }

        return ret;
    }
};

int main()
{
    Tile big_tile;
    big_tile.number = 69; // just so it is initialised // nice

    {
        std::map<int, std::map<int, Tile>> map;

        {
            std::vector<Tile> tiles;

            { // input data
                std::string line;
                std::ifstream in("input");

                Tile tile;

                while (std::getline(in, line))
                {
                    if (line.length() != 0)
                    {
                        std::smatch match;

                        if (std::regex_search(line, match, std::regex("Tile (\\d+):")))
                        {
                            tile.number = std::stoi(match[1]);
                        }
                        else
                        {
                            std::vector<bool> tile_line;

                            for (char const c : line)
                            {
                                tile_line.push_back(c == '#');
                            }

                            tile.image.push_back(tile_line);
                        }
                    }
                    else
                    {
                        tiles.push_back(tile);
                        tile.image.clear();
                    }
                }

                tiles.push_back(tile);
            }

            std::map<int, std::map<int, bool>> filled_spots; // to not touch the bigger map unnecessarily, to not make finding corners there hard

            map[0][0] = tiles[0]; // initial starting point of the search
            filled_spots[0][0] = 1;
            tiles.erase(tiles.begin());

            std::queue<std::pair<int, int>> q; // search queue
            q.push({1, 0});
            q.push({0, 1});
            q.push({-1, 0});
            q.push({0, -1});

            while (!q.empty() && tiles.size() > 0)
            {
                const std::pair<int, int> top = q.front();
                q.pop();

                const int x = top.first;
                const int y = top.second;

                if (filled_spots[x][y])
                {
                    continue;
                }

                // top right bottom left
                int neighbours = 0;

                neighbours += filled_spots[x][y + 1];
                neighbours *= 2;
                neighbours += filled_spots[x + 1][y];
                neighbours *= 2;
                neighbours += filled_spots[x][y - 1];
                neighbours *= 2;
                neighbours += filled_spots[x - 1][y];

                std::size_t count = 0;

                switch (neighbours)
                {
                case 1: // left
                {
                    const std::vector<bool> to_match_left = map[x - 1][y].get_right();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_left() == to_match_left)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_left_flipped() == to_match_left)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_right() == to_match_left)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_right_flipped() == to_match_left)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 2: // bottom
                {
                    const std::vector<bool> to_match_bottom = map[x][y - 1].get_top();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_bottom() == to_match_bottom)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom_flipped() == to_match_bottom)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top() == to_match_bottom)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top_flipped() == to_match_bottom)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 3: // left bottom
                {
                    const std::vector<bool> to_match_left = map[x - 1][y].get_right();
                    const std::vector<bool> to_match_bottom = map[x][y - 1].get_top();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_left() == to_match_left && i.get_bottom() == to_match_bottom)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_right() == to_match_left && i.get_bottom_flipped() == to_match_bottom)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_left_flipped() == to_match_left && i.get_top() == to_match_bottom)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_right_flipped() == to_match_left && i.get_top_flipped() == to_match_bottom)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 4: // right
                {
                    const std::vector<bool> to_match_right = map[x + 1][y].get_left();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_right() == to_match_right)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_right_flipped() == to_match_right)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_left() == to_match_right)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_left_flipped() == to_match_right)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 5: // left right
                {
                    const std::vector<bool> to_match_left = map[x - 1][y].get_right();
                    const std::vector<bool> to_match_right = map[x + 1][y].get_left();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_left() == to_match_left && i.get_right() == to_match_right)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_left_flipped() == to_match_left && i.get_right_flipped() == to_match_right)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_right() == to_match_left && i.get_left() == to_match_right)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_right_flipped() == to_match_left && i.get_left_flipped() == to_match_right)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 6: // bottom right
                {
                    const std::vector<bool> to_match_right = map[x + 1][y].get_left();
                    const std::vector<bool> to_match_bottom = map[x][y - 1].get_top();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_right() == to_match_right && i.get_bottom() == to_match_bottom)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_right_flipped() == to_match_right && i.get_top() == to_match_bottom)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_left() == to_match_right && i.get_bottom_flipped() == to_match_bottom)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_left_flipped() == to_match_right && i.get_top_flipped() == to_match_bottom)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 7: // bottom left right
                {
                    const std::vector<bool> to_match_bottom = map[x][y - 1].get_top();
                    const std::vector<bool> to_match_left = map[x - 1][y].get_right();
                    const std::vector<bool> to_match_right = map[x + 1][y].get_left();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_bottom() == to_match_bottom && i.get_left() == to_match_left && i.get_right() == to_match_right)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top() == to_match_bottom && i.get_left_flipped() == to_match_left && i.get_right_flipped() == to_match_right)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom_flipped() == to_match_bottom && i.get_right() == to_match_left && i.get_left() == to_match_right)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top_flipped() == to_match_bottom && i.get_right_flipped() == to_match_left && i.get_left_flipped() == to_match_right)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 8: // top
                {
                    const std::vector<bool> to_match_top = map[x][y + 1].get_bottom();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_top() == to_match_top)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom() == to_match_top)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top_flipped() == to_match_top)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom_flipped() == to_match_top)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 9: // top left
                {
                    const std::vector<bool> to_match_top = map[x][y + 1].get_bottom();
                    const std::vector<bool> to_match_left = map[x - 1][y].get_right();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_top() == to_match_top && i.get_left() == to_match_left)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom() == to_match_top && i.get_left_flipped() == to_match_left)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top_flipped() == to_match_top && i.get_right() == to_match_left)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom_flipped() == to_match_top && i.get_right_flipped() == to_match_left)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 10: // top bottom
                {
                    const std::vector<bool> to_match_top = map[x][y + 1].get_bottom();
                    const std::vector<bool> to_match_bottom = map[x][y - 1].get_top();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_top() == to_match_top && i.get_bottom() == to_match_bottom)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom() == to_match_top && i.get_top() == to_match_bottom)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top_flipped() == to_match_top && i.get_bottom_flipped() == to_match_bottom)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom_flipped() == to_match_top && i.get_top_flipped() == to_match_bottom)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 11: // top bottom left
                {
                    const std::vector<bool> to_match_top = map[x][y + 1].get_bottom();
                    const std::vector<bool> to_match_bottom = map[x][y - 1].get_top();
                    const std::vector<bool> to_match_left = map[x - 1][y].get_right();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_top() == to_match_top && i.get_bottom() == to_match_bottom && i.get_left() == to_match_left)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom() == to_match_top && i.get_top() == to_match_bottom && i.get_left_flipped() == to_match_left)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top_flipped() == to_match_top && i.get_bottom_flipped() == to_match_bottom && i.get_right() == to_match_left)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom_flipped() == to_match_top && i.get_top_flipped() == to_match_bottom && i.get_right_flipped() == to_match_left)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 12: // top right
                {
                    const std::vector<bool> to_match_top = map[x][y + 1].get_bottom();
                    const std::vector<bool> to_match_right = map[x + 1][y].get_left();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_top() == to_match_top && i.get_right() == to_match_right)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom() == to_match_top && i.get_right_flipped() == to_match_right)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top_flipped() == to_match_top && i.get_left() == to_match_right)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom_flipped() == to_match_top && i.get_left_flipped() == to_match_right)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 13: // top right left
                {
                    const std::vector<bool> to_match_top = map[x][y + 1].get_bottom();
                    const std::vector<bool> to_match_right = map[x + 1][y].get_left();
                    const std::vector<bool> to_match_left = map[x - 1][y].get_right();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_top() == to_match_top && i.get_right() == to_match_right && i.get_left() == to_match_left)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom() == to_match_top && i.get_right_flipped() == to_match_right && i.get_left_flipped() == to_match_left)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top_flipped() == to_match_top && i.get_left() == to_match_right && i.get_right() == to_match_left)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom_flipped() == to_match_top && i.get_left_flipped() == to_match_right && i.get_right_flipped() == to_match_left)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 14: // top right bottom
                {
                    const std::vector<bool> to_match_top = map[x][y + 1].get_bottom();
                    const std::vector<bool> to_match_right = map[x + 1][y].get_left();
                    const std::vector<bool> to_match_bottom = map[x][y - 1].get_top();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_top() == to_match_top && i.get_right() == to_match_right && i.get_bottom() == to_match_bottom)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom() == to_match_top && i.get_right_flipped() == to_match_right && i.get_top() == to_match_bottom)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top_flipped() == to_match_top && i.get_left() == to_match_right && i.get_bottom_flipped() == to_match_bottom)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom_flipped() == to_match_top && i.get_left_flipped() == to_match_right && i.get_top_flipped() == to_match_bottom)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                case 15:
                {
                    const std::vector<bool> to_match_top = map[x][y + 1].get_bottom();
                    const std::vector<bool> to_match_right = map[x + 1][y].get_left();
                    const std::vector<bool> to_match_bottom = map[x][y - 1].get_top();
                    const std::vector<bool> to_match_left = map[x - 1][y].get_right();

                    for (Tile &i : tiles)
                    {
                        for (int c = 0; c < 2; c++)
                        {
                            if (i.get_top() == to_match_top && i.get_right() == to_match_right && i.get_bottom() == to_match_bottom && i.get_left() == to_match_left)
                            {
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom() == to_match_top && i.get_right_flipped() == to_match_right && i.get_top() == to_match_bottom && i.get_left_flipped() == to_match_left)
                            {
                                i.flip_upside_down();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_top_flipped() == to_match_top && i.get_left() == to_match_right && i.get_bottom_flipped() == to_match_bottom && i.get_right() == to_match_left)
                            {
                                i.flip_left_right();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            if (i.get_bottom_flipped() == to_match_top && i.get_left_flipped() == to_match_right && i.get_top_flipped() == to_match_bottom && i.get_right_flipped() == to_match_left)
                            {
                                i.flip_both();
                                map[x][y] = i;
                                filled_spots[x][y] = 1;
                                break;
                            }

                            i.rotate();
                        }

                        if (filled_spots[x][y])
                        {
                            break;
                        }

                        count++;
                    }
                }
                break;
                default:
                    count = tiles.size();
                    break;
                }

                if (count < tiles.size())
                {
                    tiles.erase(tiles.begin() + count);

                    q.push({x - 1, y});
                    q.push({x + 1, y});
                    q.push({x, y - 1});
                    q.push({x, y + 1});
                }
            }

            int64_t answer = 1;

            answer *= map.begin()->second.begin()->second.number;
            answer *= map.begin()->second.rbegin()->second.number;
            answer *= map.rbegin()->second.begin()->second.number;
            answer *= map.rbegin()->second.rbegin()->second.number;

            std::cout << "Part 1: " << answer << '\n';
        }

        {
            for (auto &i : map)
            {
                for (auto &j : i.second)
                {
                    j.second.remove_borders();
                }
            }

            const int y_begin = map[0].rbegin()->first;
            const int y_end = map[0].begin()->first;
            const int x_begin = map.begin()->first;
            const int x_end = map.rbegin()->first;
            const std::size_t lines = map[0][0].image.size();

            for (int y = y_begin; y >= y_end; y--)
            {
                for (std::size_t i = 0; i < lines; i++)
                {
                    std::vector<bool> line;

                    for (int x = x_begin; x <= x_end; x++)
                    {
                        for (bool const b : map[x][y].image[i])
                        {
                            line.push_back(b);
                        }
                    }

                    big_tile.image.push_back(line);
                }
            }
        }
    }

    const std::array<std::array<bool, 20>, 3> monster = {{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                                          {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1},
                                                          {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}}};

    for (int i = 0; i < 8; i++)
    {
        int count = 0;

        for (std::size_t i = 0; i < big_tile.image[0].size() - 20; i++)
        {
            for (std::size_t j = 0; j < big_tile.image.size() - 3; j++)
            {
                if ([i, j, &big_tile, &monster]() {
                        for (std::size_t x = i; x < i + 20; x++)
                        {
                            for (std::size_t y = j; y < j + 3; y++)
                            {
                                if (monster[y - j][x - i] && !big_tile.image[x][y])
                                {
                                    return false;
                                }
                            }
                        }

                        return true;
                    }())
                {
                    count++;
                }
            }
        }

        if (count > 0)
        {
            int sum = 0;

            for (auto const i : big_tile.image)
            {
                for (auto const j : i)
                {
                    sum += j;
                }
            }

            sum -= count * 15;

            std::cout << "Part 2: " << sum << '\n';
            return 0;
        }

        switch (i % 4)
        {
        case 3:
            big_tile.flip_upside_down();
            big_tile.rotate();
            break;
        case 0:
        case 2:
            big_tile.flip_left_right();
        case 1:
            big_tile.flip_upside_down();
        default:
            break;
        }
    }
}