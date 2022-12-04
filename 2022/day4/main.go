package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func part1() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	sum := 0

	for fileScanner.Scan() {
		line := fileScanner.Text()

		pairs := strings.Split(line, ",")

		splitPairs := [2][]string{strings.Split(pairs[0], "-"), strings.Split(pairs[1], "-")}

		converted := [2][2]int{}

		for i := 0; i < 2; i++ {
			for j := 0; j < 2; j++ {
				num, err := strconv.Atoi(splitPairs[i][j])

				if err != nil {
					fmt.Println(err)
				}

				converted[i][j] = num
			}
		}

		if converted[0][0] > converted[1][0] {
			converted[0], converted[1] = converted[1], converted[0]
		}

		if converted[0][0] == converted[1][0] && converted[0][1] < converted[1][1] {
			converted[0], converted[1] = converted[1], converted[0]
		}

		if converted[1][1] <= converted[0][1] {
			sum++
		}
	}

	readFile.Close()

	fmt.Println(sum)
}

func part2() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	sum := 0

	for fileScanner.Scan() {
		line := fileScanner.Text()

		pairs := strings.Split(line, ",")

		splitPairs := [2][]string{strings.Split(pairs[0], "-"), strings.Split(pairs[1], "-")}

		converted := [2][2]int{}

		for i := 0; i < 2; i++ {
			for j := 0; j < 2; j++ {
				num, err := strconv.Atoi(splitPairs[i][j])

				if err != nil {
					fmt.Println(err)
				}

				converted[i][j] = num
			}
		}

		if converted[0][0] > converted[1][0] {
			converted[0], converted[1] = converted[1], converted[0]
		}

		if converted[0][0] == converted[1][0] && converted[0][1] < converted[1][1] {
			converted[0], converted[1] = converted[1], converted[0]
		}

		if converted[1][0] <= converted[0][1] {
			sum++
		}
	}

	readFile.Close()

	fmt.Println(sum)
}

func main() {
	part1()
	part2()
}
