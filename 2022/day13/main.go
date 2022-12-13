package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

type PacketList struct {
	number int
	list   []PacketList
	isList bool
}

func parser(data string) (packets PacketList, skip int) {
	numberString := ""

	packets.isList = true

	for skip = 1; skip < len(data); skip++ {
		switch data[skip] {
		case '[':
			packs, manySkip := parser(data[skip:])

			packets.list = append(packets.list, packs)

			skip += manySkip
		case ']':
			if len(numberString) > 0 {
				number, err := strconv.Atoi(numberString)

				if err != nil {
					fmt.Println(err)
				}

				pack := PacketList{}
				pack.number = number

				packets.list = append(packets.list, pack)
			}

			return
		case ',':
			if len(numberString) > 0 {

				number, err := strconv.Atoi(numberString)

				if err != nil {
					fmt.Println(err)
				}

				pack := PacketList{}
				pack.number = number

				packets.list = append(packets.list, pack)
				numberString = ""
			}
		default:
			numberString += string(data[skip])
		}
	}

	return
}

// if correct = 1; if equal = 0; if wrong = -1
func compare(l PacketList, r PacketList) int {
	if l.isList != r.isList {
		if !l.isList {
			newPack := PacketList{}

			newPack.list = append(newPack.list, l)
			newPack.isList = true

			l = newPack
		} else {
			newPack := PacketList{}

			newPack.list = append(newPack.list, r)
			newPack.isList = true

			r = newPack
		}
	}

	if l.isList {
		returnee := 0
		length := len(l.list)

		if len(l.list) < len(r.list) {
			returnee = 1
			length = len(l.list)
		} else if len(l.list) > len(r.list) {
			returnee = -1
			length = len(r.list)
		}

		for i := 0; i < length; i++ {
			result := compare(l.list[i], r.list[i])

			if result != 0 {
				return result
			}
		}

		return returnee
	} else {
		if l.number < r.number {
			return 1
		} else if l.number > r.number {
			return -1
		} else {
			return 0
		}
	}
}

func part1() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(func(data []byte, atEOF bool) (advance int, token []byte, err error) {
		regex, regexError := regexp.Compile(`(\n\n|\n$)`)

		if regexError != nil {
			err = regexError
			fmt.Println(err)
		}

		loc := regex.FindIndex(data)

		if loc != nil {
			advance = loc[1]
			token = data[:loc[0]]
		}

		return
	})

	sum := 0
	index := 1

	for fileScanner.Scan() {
		pair := fileScanner.Text()

		lines := strings.Split(pair, "\n")

		left, _ := parser(lines[0])
		right, _ := parser(lines[1])

		if compare(left, right) > 0 {
			sum += index
		}

		index++
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

	packets := []PacketList{}

	popUpSort := func() int {
		cont := true
		i := len(packets) - 2

		for ; i >= 0 && cont; i-- {
			cont = false

			if compare(packets[i+1], packets[i]) > 0 {
				cont = true
				packets[i+1], packets[i] = packets[i], packets[i+1]
			}
		}

		// one for one-indexing,
		// one for it being one further,
		// one for an additional iteration of the loop
		// for a total of 3
		return i + 3
	}

	for fileScanner.Scan() {
		line := fileScanner.Text()

		if len(line) > 0 {
			packet, _ := parser(line)

			packets = append(packets, packet)

			popUpSort()
		}
	}

	multi := 1

	add := func(number int) int {
		packet := PacketList{}
		packet.isList = true

		innerPacket := PacketList{}
		innerPacket.isList = true

		innerestPacket := PacketList{}
		innerestPacket.number = number

		innerPacket.list = append(innerPacket.list, innerestPacket)
		packet.list = append(packet.list, innerPacket)

		packets = append(packets, packet)

		return popUpSort()
	}

	multi *= add(2)
	multi *= add(6)

	readFile.Close()
	fmt.Println(multi)
}

func main() {
	part1()
	part2()
}
