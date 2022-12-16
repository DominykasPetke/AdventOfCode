package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Coords struct {
	x int
	y int
}

func readRocks(file string) (rocks map[int]map[int]bool, lowestY int) {
	rocks = make(map[int]map[int]bool)
	readFile, err := os.Open(file)

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	for fileScanner.Scan() {
		line := fileScanner.Text()

		coords := strings.Split(line, " -> ")

		from := Coords{}

		for index, coord := range coords {
			values := strings.Split(coord, ",")

			number, err := strconv.Atoi(values[0])

			if err != nil {
				fmt.Println(err)
			}

			to := Coords{}
			to.x = number

			number, err = strconv.Atoi(values[1])

			if err != nil {
				fmt.Println(err)
			}

			to.y = number

			if number > lowestY {
				lowestY = number
			}

			if index != 0 {
				minY, maxY := from.y, to.y

				if to.y < minY {
					minY, maxY = to.y, from.y
				}

				for y := minY; y <= maxY; y++ {
					_, ok := rocks[y]

					if !ok {
						rocks[y] = make(map[int]bool)
					}

					rocks[y][from.x] = true
				}

				minX, maxX := from.x, to.x

				if to.x < minX {
					minX, maxX = to.x, from.x
				}

				for x := minX; x <= maxX; x++ {
					_, ok := rocks[from.y]

					if !ok {
						rocks[from.y] = make(map[int]bool)
					}

					rocks[from.y][x] = true
				}
			}

			from = to
		}
	}

	readFile.Close()
	return
}

func part1() {
	rocks, lowestY := readRocks("input")

	sum := 0

	for {
		sand := Coords{500, 0}

		falling := true

		for falling {
			falling = false

			if sand.y > lowestY {

			} else if !rocks[sand.y+1][sand.x] {
				sand.y++
				falling = true
			} else if !rocks[sand.y+1][sand.x-1] {
				sand.y++
				sand.x--
				falling = true
			} else if !rocks[sand.y+1][sand.x+1] {
				sand.y++
				sand.x++
				falling = true
			}
		}

		if sand.y > lowestY {
			fmt.Println(sum)
			return
		}

		_, ok := rocks[sand.y]

		if !ok {
			rocks[sand.y] = make(map[int]bool)
		}

		sum++
		rocks[sand.y][sand.x] = true
	}
}

func part2() {
	rocks, floor := readRocks("input")
	floor += 2

	sum := 0

	for {
		sand := Coords{500, 0}

		falling := true

		for falling {
			falling = false

			if sand.y+1 >= floor {

			} else if !rocks[sand.y+1][sand.x] {
				sand.y++
				falling = true
			} else if !rocks[sand.y+1][sand.x-1] {
				sand.y++
				sand.x--
				falling = true
			} else if !rocks[sand.y+1][sand.x+1] {
				sand.y++
				sand.x++
				falling = true
			}
		}

		if sand.y == 0 && sand.x == 500 {
			sum++
			fmt.Println(sum)
			return
		}

		_, ok := rocks[sand.y]

		if !ok {
			rocks[sand.y] = make(map[int]bool)
		}

		sum++
		rocks[sand.y][sand.x] = true
	}
}

func main() {
	part1()
	part2()
}
