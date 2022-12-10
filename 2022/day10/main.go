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
	register := 1

	cycleCount := 1

	after := func() {
		cycleCount++

		switch cycleCount {
		case 20:
			fallthrough
		case 60:
			fallthrough
		case 100:
			fallthrough
		case 140:
			fallthrough
		case 180:
			fallthrough
		case 220:
			sum += cycleCount * register
		}
	}

	for fileScanner.Scan() {
		line := fileScanner.Text()

		split := strings.Split(line, " ")

		switch split[0] {
		case "noop":
			after()
		case "addx":
			num, err := strconv.Atoi(split[1])

			if err != nil {
				fmt.Println(err)
			}

			after()
			register += num
			after()
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

	register := 1

	cycleCount := 0

	output := ""

	after := func() {
		diff := (cycleCount % 40) - register

		if diff < 0 {
			diff = -diff
		}

		if diff <= 1 {
			output += "#"
		} else {
			output += "."
		}

		if cycleCount%40 == 39 {
			output += "\n"
		}

		cycleCount++
	}

	for fileScanner.Scan() {
		line := fileScanner.Text()

		split := strings.Split(line, " ")

		switch split[0] {
		case "noop":
			after()
		case "addx":
			num, err := strconv.Atoi(split[1])

			if err != nil {
				fmt.Println(err)
			}

			after()
			after()
			register += num
		}
	}

	readFile.Close()

	fmt.Println(output)
}

func main() {
	part1()
	part2()
}
