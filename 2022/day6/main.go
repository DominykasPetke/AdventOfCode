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

	defer readFile.Close()

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	for fileScanner.Scan() {
		line := fileScanner.Text()

		lastFour := [4]rune{}

		for index, char := range line {
			lastFour[index%4] = char

			if index < 3 {
				continue
			}

			// if we found 4 different characters
			if func(chars [4]rune) bool {
				for index, char := range chars {
					for i := index + 1; i < 4; i++ {
						if char == chars[i] {
							return false
						}
					}
				}

				return true
			}(lastFour) {
				fmt.Println(index + 1)
				return
			}
		}
	}
}

func part2() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	defer readFile.Close()

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	for fileScanner.Scan() {
		line := fileScanner.Text()

		lastFourteen := [14]rune{}

		for index, char := range line {
			lastFourteen[index%14] = char

			if index < 13 {
				continue
			}

			// if we found 14 different characters
			if func(chars [14]rune) bool {
				for index, char := range chars {
					for i := index + 1; i < 14; i++ {
						if char == chars[i] {
							return false
						}
					}
				}

				return true
			}(lastFourteen) {
				fmt.Println(index + 1)
				return
			}
		}
	}
}

func main() {
	part1()
	part2()
}
