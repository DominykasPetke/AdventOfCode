package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
)

func part1() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	count := 0
	max := 0

	for fileScanner.Scan() {
		line := fileScanner.Text()

		if line == "" {
			if count > max {
				max = count
			}

			count = 0
		} else {
			num, err := strconv.Atoi(line)

			if err != nil {
				fmt.Println(err)
			}

			count += num
		}
	}

	readFile.Close()

	fmt.Println(max)
}

func part2() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)

	fileScanner.Split(bufio.ScanLines)

	count := 0
	var max = [3]int{0, 0, 0}

	for fileScanner.Scan() {
		line := fileScanner.Text()

		if line == "" {
			if count > max[0] {
				max[0] = count
				sort.Ints(max[:])
			}

			count = 0
		} else {
			num, err := strconv.Atoi(line)

			if err != nil {
				fmt.Println(err)
			}

			count += num
		}
	}

	readFile.Close()

	sum := 0

	for _, num := range max {
		sum += num
	}

	fmt.Println(sum)
}

func main() {
	part1()
	part2()
}
