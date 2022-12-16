package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"github.com/golang-collections/go-datastructures/queue"
)

func part1() {
	readFile, err := os.Open("input")
	beaconLine := 2000000

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	scan := make(map[int]int) // 1 is beacon, 2 is can't be

	sum := 0

	for fileScanner.Scan() {
		line := fileScanner.Text()

		coords := strings.Split(line, "=")

		number, err := strconv.Atoi(strings.Split(coords[1], ",")[0])

		if err != nil {
			fmt.Println(err)
		}

		sensorX := number

		number, err = strconv.Atoi(strings.Split(coords[2], ":")[0])

		if err != nil {
			fmt.Println(err)
		}

		sensorY := number

		number, err = strconv.Atoi(strings.Split(coords[3], ",")[0])

		if err != nil {
			fmt.Println(err)
		}

		beaconX := number

		number, err = strconv.Atoi(coords[4])

		if err != nil {
			fmt.Println(err)
		}

		beaconY := number

		if beaconY == beaconLine {
			if scan[beaconX] == 2 {
				sum--
			}

			scan[beaconX] = 1
		}

		diffX := sensorX - beaconX

		if diffX < 0 {
			diffX = -diffX
		}

		diffY := sensorY - beaconY

		if diffY < 0 {
			diffY = -diffY
		}

		distance := diffX + diffY

		distToBeaconLine := sensorY - beaconLine

		if distToBeaconLine < 0 {
			distToBeaconLine = -distToBeaconLine
		}

		beaconDiff := distance - distToBeaconLine

		if beaconDiff >= 0 {
			for x := sensorX - beaconDiff; x <= sensorX+beaconDiff; x++ {
				if scan[x] == 0 {
					scan[x] = 2
					sum++
				}
			}
		}
	}

	readFile.Close()
	fmt.Println(sum)
}

type Sensor struct {
	x        int
	y        int
	distance int
}

type Square struct {
	minX int
	minY int
	maxX int
	maxY int
}

type Item struct {
	square Square
	count  int
}

func (i Item) Compare(other queue.Item) int {
	oth := other.(Item)

	if i.count == oth.count {
		if i.square.minX == oth.square.minX {
			if i.square.minY == oth.square.minY {
				if i.square.maxX == oth.square.maxX {
					if i.square.maxY == oth.square.maxY {
						return 0
					}

					if i.square.maxY < oth.square.maxY {
						return 1
					} else {
						return -1
					}
				}

				if i.square.maxX < oth.square.maxX {
					return 1
				} else {
					return -1
				}
			}

			if i.square.minY < oth.square.minY {
				return 1
			} else {
				return -1
			}
		}

		if i.square.minX > oth.square.minX {
			return 1
		} else {
			return -1
		}
	}

	if i.count > oth.count {
		return 1
	} else {
		return -1
	}
}

func part2() {
	readFile, err := os.Open("input")
	max := 4000000
	// max := 20

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	sensors := []Sensor{}

	for fileScanner.Scan() {
		line := fileScanner.Text()

		coords := strings.Split(line, "=")

		number, err := strconv.Atoi(strings.Split(coords[1], ",")[0])

		if err != nil {
			fmt.Println(err)
		}

		sensorX := number

		number, err = strconv.Atoi(strings.Split(coords[2], ":")[0])

		if err != nil {
			fmt.Println(err)
		}

		sensorY := number

		number, err = strconv.Atoi(strings.Split(coords[3], ",")[0])

		if err != nil {
			fmt.Println(err)
		}

		beaconX := number

		number, err = strconv.Atoi(coords[4])

		if err != nil {
			fmt.Println(err)
		}

		beaconY := number

		diffX := sensorX - beaconX

		if diffX < 0 {
			diffX = -diffX
		}

		diffY := sensorY - beaconY

		if diffY < 0 {
			diffY = -diffY
		}

		distance := diffX + diffY

		sensors = append(sensors, Sensor{sensorX, sensorY, distance})
	}

	readFile.Close()

	countSensors := func(square Square) (sum int, allMatch bool) {
		topLeft := []Sensor{}
		topRight := []Sensor{}
		bottomLeft := []Sensor{}
		bottomRight := []Sensor{}

		for _, sensor := range sensors {
			newSquare := Square{square.minX - sensor.distance, square.minY - sensor.distance, square.maxX + sensor.distance, square.maxY + sensor.distance}

			if sensor.x >= newSquare.minX && sensor.x <= newSquare.maxX && sensor.y >= newSquare.minY && sensor.y <= newSquare.maxY {
				sum++

				if sensor.x < square.minX && sensor.y < square.minY {
					sum--

					diffX := sensor.x - square.minX

					if diffX < 0 {
						diffX = -diffX
					}

					diffY := sensor.y - square.minY

					if diffY < 0 {
						diffY = -diffY
					}

					distance := diffX + diffY

					if distance <= sensor.distance {
						sum++
					}
				} else if sensor.x > square.maxX && sensor.y >= square.maxY {
					sum--

					diffX := sensor.x - square.maxX

					if diffX < 0 {
						diffX = -diffX
					}

					diffY := sensor.y - square.maxY

					if diffY < 0 {
						diffY = -diffY
					}

					distance := diffX + diffY

					if distance <= sensor.distance {
						sum++
					}
				} else if sensor.x < square.minX && sensor.y > square.maxY {
					sum--

					diffX := sensor.x - square.minX

					if diffX < 0 {
						diffX = -diffX
					}

					diffY := sensor.y - square.maxY

					if diffY < 0 {
						diffY = -diffY
					}

					distance := diffX + diffY

					if distance <= sensor.distance {
						sum++
					}
				} else if sensor.x > square.maxX && sensor.y < square.minY {
					sum--

					diffX := sensor.x - square.maxX

					if diffX < 0 {
						diffX = -diffX
					}

					diffY := sensor.y - square.minY

					if diffY < 0 {
						diffY = -diffY
					}

					distance := diffX + diffY

					if distance <= sensor.distance {
						sum++
					}
				}
			}

			diffX := sensor.x - square.minX

			if diffX < 0 {
				diffX = -diffX
			}

			diffY := sensor.y - square.minY

			if diffY < 0 {
				diffY = -diffY
			}

			distance := diffX + diffY

			if distance <= sensor.distance {
				topLeft = append(topLeft, sensor)
			}

			diffY = sensor.y - square.maxY

			if diffY < 0 {
				diffY = -diffY
			}

			distance = diffX + diffY

			if distance <= sensor.distance {
				topRight = append(topRight, sensor)
			}

			diffX = sensor.x - square.maxX

			if diffX < 0 {
				diffX = -diffX
			}

			diffY = sensor.y - square.minY

			if diffY < 0 {
				diffY = -diffY
			}

			distance = diffX + diffY

			if distance <= sensor.distance {
				bottomLeft = append(bottomLeft, sensor)
			}

			diffY = sensor.y - square.maxY

			if diffY < 0 {
				diffY = -diffY
			}

			distance = diffX + diffY

			if distance <= sensor.distance {
				bottomRight = append(bottomRight, sensor)
			}
		}

		if len(topLeft) == len(topRight) && len(topLeft) == len(bottomLeft) && len(topLeft) == len(bottomRight) && len(topLeft) > 0 {
			for index, sens := range topLeft {
				if topRight[index] != sens || bottomLeft[index] != sens || bottomRight[index] != sens {
					allMatch = false
					return
				}
			}

			allMatch = true
			return
		} else {
			allMatch = false
			return
		}
	}

	pQueue := queue.NewPriorityQueue(4)

	count, _ := countSensors(Square{0, 0, max, max})

	pQueue.Put(Item{Square{0, 0, max, max}, count})

	for !pQueue.Empty() {
		top := (pQueue.Peek()).(Item)
		_, err := pQueue.Get(1)

		if err != nil {
			fmt.Println(err)
		}

		if top.count == 0 {
			sum := top.square.minX*4000000 + top.square.minY
			fmt.Println(sum)
			return
		}

		// divide into 4
		midX := (top.square.minX + top.square.maxX) / 2
		midY := (top.square.minY + top.square.maxY) / 2

		square := Square{top.square.minX, top.square.minY, midX, midY}
		count, test := countSensors(square)

		if (square.minX != square.maxX || square.minY != square.maxY || count == 0) && !test {
			pQueue.Put(Item{square, count})
		}

		if midY != top.square.maxY {
			square = Square{top.square.minX, midY + 1, midX, top.square.maxY}
			count, test := countSensors(square)

			if (square.minX != square.maxX || square.minY != square.maxY || count == 0) && !test {
				pQueue.Put(Item{square, count})
			}
		}

		if midX != top.square.maxX {
			square = Square{midX + 1, top.square.minY, top.square.maxX, midY}
			count, test := countSensors(square)

			if (square.minX != square.maxX || square.minY != square.maxY || count == 0) && !test {
				pQueue.Put(Item{square, count})
			}
		}

		if midX != top.square.maxX && midY != top.square.maxY {
			square = Square{midX + 1, midY + 1, top.square.maxX, top.square.maxY}
			count, test := countSensors(square)

			if (square.minX != square.maxX || square.minY != square.maxY || count == 0) && !test {
				pQueue.Put(Item{square, count})
			}
		}
	}
}

func main() {
	part1()
	part2()
}
