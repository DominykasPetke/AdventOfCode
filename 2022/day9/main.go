package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func part1() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	tailMap := make(map[int]map[int]bool)

	currentHeadX := 0
	currentHeadY := 0

	currentTailX := 0
	currentTailY := 0

	for fileScanner.Scan() {
		line := fileScanner.Text()

		number, err := strconv.Atoi(line[2:])

		if err != nil {
			fmt.Println(err)
		}

		for i := 0; i < number; i++ {
			switch line[0] {
			case 'R':
				currentHeadX++

				if currentHeadX-1 > currentTailX {
					currentTailX = currentHeadX - 1
					currentTailY = currentHeadY
				}

			case 'L':
				currentHeadX--

				if currentHeadX < currentTailX-1 {
					currentTailX = currentHeadX + 1
					currentTailY = currentHeadY
				}

			case 'U':
				currentHeadY++

				if currentHeadY-1 > currentTailY {
					currentTailX = currentHeadX
					currentTailY = currentHeadY - 1
				}

			case 'D':
				currentHeadY--

				if currentHeadY < currentTailY-1 {
					currentTailX = currentHeadX
					currentTailY = currentHeadY + 1
				}
			}

			if tailMap[currentTailX] == nil {
				tailMap[currentTailX] = make(map[int]bool)
			}

			tailMap[currentTailX][currentTailY] = true
		}
	}

	readFile.Close()

	count := 0

	for _, oneMap := range tailMap {
		for _, bools := range oneMap {
			if bools {
				count++
			}
		}
	}

	fmt.Println(count)
}

type Knot struct {
	x int
	y int
}

func part2() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	tailMap := make(map[int]map[int]bool)

	rope := [10]Knot{}

	for fileScanner.Scan() {
		line := fileScanner.Text()

		number, err := strconv.Atoi(line[2:])

		if err != nil {
			fmt.Println(err)
		}

		mover := func(head Knot, tail Knot) (bool, Knot) {
			moved := false

			if head.x-1 > tail.x && head.y-1 > tail.y {
				tail.x = head.x - 1
				tail.y = head.y - 1

				moved = true
			} else if head.x-1 > tail.x && head.y < tail.y-1 {
				tail.x = head.x - 1
				tail.y = head.y + 1

				moved = true
			} else if head.x < tail.x-1 && head.y-1 > tail.y {
				tail.x = head.x + 1
				tail.y = head.y - 1

				moved = true
			} else if head.x < tail.x-1 && head.y < tail.y-1 {
				tail.x = head.x + 1
				tail.y = head.y + 1

				moved = true
			} else if head.x-1 > tail.x {
				tail.x = head.x - 1
				tail.y = head.y

				moved = true
			} else if head.x < tail.x-1 {
				tail.x = head.x + 1
				tail.y = head.y

				moved = true
			} else if head.y-1 > tail.y {
				tail.x = head.x
				tail.y = head.y - 1

				moved = true
			} else if head.y < tail.y-1 {
				tail.x = head.x
				tail.y = head.y + 1

				moved = true
			}

			return moved, tail
		}

		for i := 0; i < number; i++ {
			switch line[0] {
			case 'R':
				rope[0].x++
			case 'L':
				rope[0].x--
			case 'U':
				rope[0].y++
			case 'D':
				rope[0].y--
			}

			keepMoving := true

			for head := 0; head < 9 && keepMoving; head++ {
				keepMoving, rope[head+1] = mover(rope[head], rope[head+1])
			}

			if tailMap[rope[9].x] == nil {
				tailMap[rope[9].x] = make(map[int]bool)
			}

			tailMap[rope[9].x][rope[9].y] = true
		}
	}

	readFile.Close()

	count := 0

	for _, oneMap := range tailMap {
		for _, bools := range oneMap {
			if bools {
				count++
			}
		}
	}

	fmt.Println(count)
}

func main() {
	part1()
	part2()
}
