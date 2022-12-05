package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func reverse(array []byte) []byte {
	newArray := make([]byte, 0, len(array))

	for i := len(array) - 1; i >= 0; i-- {
		newArray = append(newArray, array[i])
	}

	return newArray
}

func part1() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	stacks := [9][]byte{}

	for fileScanner.Scan() {
		line := fileScanner.Text()

		if len(line) == 0 {
			for index, array := range stacks {
				stacks[index] = reverse(array)
			}
		} else if line[0] == 'm' {
			pairs := strings.Split(line, " ")

			num, err := strconv.Atoi(pairs[1])

			if err != nil {
				fmt.Println(err)
			}

			count := num

			num, err = strconv.Atoi(pairs[3])

			if err != nil {
				fmt.Println(err)
			}

			from := num - 1

			num, err = strconv.Atoi(pairs[5])

			if err != nil {
				fmt.Println(err)
			}

			to := num - 1

			for i := 0; i < count; i++ {
				x := stacks[from][len(stacks[from])-1]
				stacks[from] = stacks[from][:len(stacks[from])-1]

				stacks[to] = append(stacks[to], x)
			}
		} else {
			for i := 0; i <= (len(line)-1)/4; i++ {
				if line[i*4+1] >= 65 && line[i*4+1] <= 90 {
					stacks[i] = append(stacks[i], line[i*4+1])
				}
			}
		}
	}

	result := ""

	for _, array := range stacks {
		result += string(array[len(array)-1])
	}

	readFile.Close()

	fmt.Println(result)
}

func part2() {
}

func main() {
	part1()
	part2()
}
