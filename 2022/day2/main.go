package main

import (
	"bufio"
	"fmt"
	"os"
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

		switch line[0] {
		case 'A': // rock
			switch line[2] {
			case 'X': // rock
				sum += 1 + 3
			case 'Y': // paper
				sum += 2 + 6
			case 'Z': // scissors
				sum += 3 + 0
			}
		case 'B': // paper
			switch line[2] {
			case 'X': // rock
				sum += 1 + 0
			case 'Y': // paper
				sum += 2 + 3
			case 'Z': // scissors
				sum += 3 + 6
			}
		case 'C': // scissors
			switch line[2] {
			case 'X': // rock
				sum += 1 + 6
			case 'Y': // paper
				sum += 2 + 0
			case 'Z': // scissors
				sum += 3 + 3
			}
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

		switch line[0] {
		case 'A': // rock
			switch line[2] {
			case 'X': // lose
				sum += 0 + 3
			case 'Y': // draw
				sum += 3 + 1
			case 'Z': // win
				sum += 6 + 2
			}
		case 'B': // paper
			switch line[2] {
			case 'X': // lose
				sum += 0 + 1
			case 'Y': // draw
				sum += 3 + 2
			case 'Z': // win
				sum += 6 + 3
			}
		case 'C': // scissors
			switch line[2] {
			case 'X': // lose
				sum += 0 + 2
			case 'Y': // draw
				sum += 3 + 3
			case 'Z': // win
				sum += 6 + 1
			}
		}
	}

	readFile.Close()

	fmt.Println(sum)
}

func main() {
	part1()
	part2()
}
