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

		var letters = make(map[byte][2]bool)

		for i := 0; i < len(line)/2; i++ {
			input := letters[line[i]]
			input[0] = true
			letters[line[i]] = input
		}

		for i := len(line) / 2; i < len(line); i++ {
			input := letters[line[i]]
			input[1] = true
			letters[line[i]] = input
		}

		for k, v := range letters {
			if v[0] && v[1] {
				if k >= 65 && k <= 90 {
					sum += int(k) - 38
					break
				} else if k >= 97 && k <= 122 {
					sum += int(k) - 96
					break
				}
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
	lineIndex := 0
	var letters = make(map[byte][3]bool)

	for fileScanner.Scan() {
		line := fileScanner.Text()

		for i := 0; i < len(line); i++ {
			input := letters[line[i]]
			input[lineIndex] = true
			letters[line[i]] = input
		}

		lineIndex++

		if lineIndex == 3 {
			lineIndex = 0

			for k, v := range letters {
				if v[0] && v[1] && v[2] {
					if k >= 65 && k <= 90 {
						sum += int(k) - 38
						break
					} else if k >= 97 && k <= 122 {
						sum += int(k) - 96
						break
					}
				}
			}

			letters = make(map[byte][3]bool)
		}
	}

	readFile.Close()

	fmt.Println(sum)
}

func main() {
	part1()
	part2()
}
