package main

import (
	"bufio"
	"fmt"
	"os"

	"github.com/golang-collections/go-datastructures/queue"
)

type Tile struct {
	height  rune
	visited bool
}

type Position struct {
	x int
	y int
}

type Item struct {
	tile     Tile
	pos      Position
	distance int
}

func (i Item) Compare(other queue.Item) int {
	oth := other.(Item)

	if i.distance == oth.distance {
		if i.tile.height == oth.tile.height {
			if i.pos.x == oth.pos.x {
				if i.pos.y == oth.pos.y {
					return 0
				}

				if i.pos.y < oth.pos.y {
					return 1
				} else {
					return -1
				}
			}

			if i.pos.x < oth.pos.x {
				return 1
			} else {
				return -1
			}
		}

		if i.tile.height > oth.tile.height {
			return 1
		} else {
			return -1
		}
	}

	if i.distance > oth.distance {
		return 1
	} else {
		return -1
	}
}

func readMap(file string) (tiles [][]Tile, startPos Position, endPos Position) {
	readFile, err := os.Open(file)

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	tiles = [][]Tile{}

	for fileScanner.Scan() {
		line := fileScanner.Text()

		tiles = append(tiles, []Tile{})

		for index, char := range line {
			if char == 'S' {
				char = 'a'
				startPos = Position{index, len(tiles) - 1}
			}

			if char == 'E' {
				char = 'z'
				endPos = Position{index, len(tiles) - 1}
			}

			tiles[len(tiles)-1] = append(tiles[len(tiles)-1], Tile{char, false})
		}
	}

	readFile.Close()
	return
}

func part1() {
	tileMap, startPos, endPos := readMap("input")

	pQueue := queue.NewPriorityQueue(1)

	pQueue.Put(Item{tileMap[startPos.y][startPos.x], Position{startPos.x, startPos.y}, 0})

	for !pQueue.Empty() {
		top := (pQueue.Peek()).(Item)
		_, err := pQueue.Get(1)

		if err != nil {
			fmt.Println(err)
		}

		if top.tile.visited {
			continue
		}

		tileMap[top.pos.y][top.pos.x].visited = true

		if top.pos == endPos {
			fmt.Println(top.distance)
			return
		}

		if top.pos.x > 0 {
			if top.tile.height+1 >= tileMap[top.pos.y][top.pos.x-1].height && !tileMap[top.pos.y][top.pos.x-1].visited {
				err := pQueue.Put(Item{tileMap[top.pos.y][top.pos.x-1], Position{top.pos.x - 1, top.pos.y}, top.distance + 1})

				if err != nil {
					fmt.Println(err)
				}
			}
		}

		if top.pos.y > 0 {
			if top.tile.height+1 >= tileMap[top.pos.y-1][top.pos.x].height && !tileMap[top.pos.y-1][top.pos.x].visited {
				err := pQueue.Put(Item{tileMap[top.pos.y-1][top.pos.x], Position{top.pos.x, top.pos.y - 1}, top.distance + 1})

				if err != nil {
					fmt.Println(err)
				}
			}
		}

		if top.pos.x < len(tileMap[top.pos.y])-1 {
			if top.tile.height+1 >= tileMap[top.pos.y][top.pos.x+1].height && !tileMap[top.pos.y][top.pos.x+1].visited {
				err := pQueue.Put(Item{tileMap[top.pos.y][top.pos.x+1], Position{top.pos.x + 1, top.pos.y}, top.distance + 1})

				if err != nil {
					fmt.Println(err)
				}
			}
		}

		if top.pos.y < len(tileMap)-1 {
			if top.tile.height+1 >= tileMap[top.pos.y+1][top.pos.x].height && !tileMap[top.pos.y+1][top.pos.x].visited {
				err := pQueue.Put(Item{tileMap[top.pos.y+1][top.pos.x], Position{top.pos.x, top.pos.y + 1}, top.distance + 1})

				if err != nil {
					fmt.Println(err)
				}
			}
		}
	}
}

func part2() {
	tileMap, _, endPos := readMap("input")

	pQueue := queue.NewPriorityQueue(1)

	for y, arr := range tileMap {
		for x, tile := range arr {
			if tile.height == 'a' {
				pQueue.Put(Item{tile, Position{x, y}, 0})
			}
		}
	}

	for !pQueue.Empty() {
		top := (pQueue.Peek()).(Item)
		_, err := pQueue.Get(1)

		if err != nil {
			fmt.Println(err)
		}

		if top.tile.visited {
			continue
		}

		tileMap[top.pos.y][top.pos.x].visited = true

		if top.pos == endPos {
			fmt.Println(top.distance)
			return
		}

		if top.pos.x > 0 {
			if top.tile.height+1 >= tileMap[top.pos.y][top.pos.x-1].height && !tileMap[top.pos.y][top.pos.x-1].visited {
				err := pQueue.Put(Item{tileMap[top.pos.y][top.pos.x-1], Position{top.pos.x - 1, top.pos.y}, top.distance + 1})

				if err != nil {
					fmt.Println(err)
				}
			}
		}

		if top.pos.y > 0 {
			if top.tile.height+1 >= tileMap[top.pos.y-1][top.pos.x].height && !tileMap[top.pos.y-1][top.pos.x].visited {
				err := pQueue.Put(Item{tileMap[top.pos.y-1][top.pos.x], Position{top.pos.x, top.pos.y - 1}, top.distance + 1})

				if err != nil {
					fmt.Println(err)
				}
			}
		}

		if top.pos.x < len(tileMap[top.pos.y])-1 {
			if top.tile.height+1 >= tileMap[top.pos.y][top.pos.x+1].height && !tileMap[top.pos.y][top.pos.x+1].visited {
				err := pQueue.Put(Item{tileMap[top.pos.y][top.pos.x+1], Position{top.pos.x + 1, top.pos.y}, top.distance + 1})

				if err != nil {
					fmt.Println(err)
				}
			}
		}

		if top.pos.y < len(tileMap)-1 {
			if top.tile.height+1 >= tileMap[top.pos.y+1][top.pos.x].height && !tileMap[top.pos.y+1][top.pos.x].visited {
				err := pQueue.Put(Item{tileMap[top.pos.y+1][top.pos.x], Position{top.pos.x, top.pos.y + 1}, top.distance + 1})

				if err != nil {
					fmt.Println(err)
				}
			}
		}
	}
}

func main() {
	part1()
	part2()
}
