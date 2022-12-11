package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

type Monkey struct {
	items          []int
	operation      func(int) int
	test           func(int) bool
	monkeyTrue     int
	monkeyFalse    int
	itemsInspected int
}

func splitFunc(data []byte, atEOF bool) (advance int, token []byte, err error) {
	regex, regexError := regexp.Compile(`(\n\n|\n$)`)

	if regexError != nil {
		fmt.Println(err)
		err = regexError
	}

	loc := regex.FindIndex(data)

	if loc != nil {
		advance = loc[1]
		token = data[:loc[0]]
	}

	return
}

func readMonkeys(file string) (monkeys []Monkey, divisor int) {
	readFile, err := os.Open(file)

	divisor = 1

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(splitFunc)

	for fileScanner.Scan() {
		line := fileScanner.Text()
		split := strings.Split(line, "\n")

		m := Monkey{}

		numbers := strings.Split(strings.Split(split[1], ": ")[1], ", ")

		for _, num := range numbers {
			number, err := strconv.Atoi(num)

			if err != nil {
				fmt.Println(err)
			}

			m.items = append(m.items, number)
		}

		spaceSplit := strings.Split(split[2], " ")
		operation := spaceSplit[6]
		second := spaceSplit[7]

		operationFunc := func(item int) int {
			switch operation {
			case "+":
				num, err := strconv.Atoi(second)

				if err != nil {
					fmt.Println(err)
				}

				return item + num
			case "*":
				switch second {
				case "old":
					return item * item
				default:
					num, err := strconv.Atoi(second)

					if err != nil {
						fmt.Println(err)
					}

					return item * num
				}
			}

			return item
		}

		m.operation = operationFunc

		spaceSplit = strings.Split(split[4], " ")
		number, err := strconv.Atoi(spaceSplit[len(spaceSplit)-1])

		if err != nil {
			fmt.Println(err)
		}

		m.monkeyTrue = number

		spaceSplit = strings.Split(split[5], " ")
		number, err = strconv.Atoi(spaceSplit[len(spaceSplit)-1])

		if err != nil {
			fmt.Println(err)
		}

		m.monkeyFalse = number

		spaceSplit = strings.Split(split[3], " ")
		number, err = strconv.Atoi(spaceSplit[len(spaceSplit)-1])

		if err != nil {
			fmt.Println(err)
		}

		m.test = func(item int) bool {
			return item%number == 0
		}

		divisor *= number

		monkeys = append(monkeys, m)
	}

	readFile.Close()
	return
}

func part1() {
	monkeys, _ := readMonkeys("input")

	for i := 0; i < 20; i++ {
		for index, monke := range monkeys {
			for _, item := range monke.items {
				item = monke.operation(item)
				item = item / 3

				if monke.test(item) {
					monkeys[monke.monkeyTrue].items = append(monkeys[monke.monkeyTrue].items, item)
				} else {
					monkeys[monke.monkeyFalse].items = append(monkeys[monke.monkeyFalse].items, item)
				}

				monke.itemsInspected++
			}

			monke.items = []int{}
			monkeys[index] = monke
		}
	}

	max1, max2 := 0, 0

	for _, monke := range monkeys {
		if monke.itemsInspected > max1 {
			max1 = monke.itemsInspected

			if max2 < max1 {
				max2, max1 = max1, max2
			}
		}
	}

	fmt.Println(max1 * max2)
}

func part2() {
	monkeys, divisor := readMonkeys("input")

	for i := 0; i < 10000; i++ {
		for index, monke := range monkeys {
			for _, item := range monke.items {
				item = monke.operation(item)

				item = item % divisor

				if monke.test(item) {
					monkeys[monke.monkeyTrue].items = append(monkeys[monke.monkeyTrue].items, item)
				} else {
					monkeys[monke.monkeyFalse].items = append(monkeys[monke.monkeyFalse].items, item)
				}

				monke.itemsInspected++
			}

			monke.items = []int{}
			monkeys[index] = monke
		}
	}

	max1, max2 := 0, 0

	for _, monke := range monkeys {
		if monke.itemsInspected > max1 {
			max1 = monke.itemsInspected

			if max2 < max1 {
				max2, max1 = max1, max2
			}
		}
	}

	fmt.Println(max1 * max2)
}

func main() {
	part1()
	part2()
}
