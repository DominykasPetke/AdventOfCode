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

	trees := [][]int{}

	for fileScanner.Scan() {
		line := fileScanner.Text()

		digits := []int{}

		for _, char := range line {
			digits = append(digits, int(char-'0'))
		}

		trees = append(trees, digits)
	}

	readFile.Close()

	count := 0

	for y, array := range trees {
		for x, tree := range array {
			if func() bool {
				left := func() bool {
					for searchX := x - 1; searchX >= 0; searchX-- {
						if tree <= trees[y][searchX] {
							return false
						}
					}

					return true
				}()

				right := func() bool {
					for searchX := x + 1; searchX < len(array); searchX++ {
						if tree <= trees[y][searchX] {
							return false
						}
					}

					return true
				}()

				up := func() bool {
					for searchY := y - 1; searchY >= 0; searchY-- {
						if tree <= trees[searchY][x] {
							return false
						}
					}

					return true
				}()

				down := func() bool {
					for searchY := y + 1; searchY < len(trees); searchY++ {
						if tree <= trees[searchY][x] {
							return false
						}
					}

					return true
				}()

				return left || right || up || down
			}() {
				count++
			}
		}
	}

	fmt.Println(count)
}

func part2() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	trees := [][]int{}

	for fileScanner.Scan() {
		line := fileScanner.Text()

		digits := []int{}

		for _, char := range line {
			digits = append(digits, int(char-'0'))
		}

		trees = append(trees, digits)
	}

	readFile.Close()

	best := 0

	for y, array := range trees {
		for x, tree := range array {
			result := func() int {
				left := func() int {
					for searchX := x - 1; searchX >= 0; searchX-- {
						if tree <= trees[y][searchX] {
							return x - searchX
						}
					}

					return x
				}()

				right := func() int {
					for searchX := x + 1; searchX < len(array); searchX++ {
						if tree <= trees[y][searchX] {
							return searchX - x
						}
					}

					return len(array) - x - 1
				}()

				up := func() int {
					for searchY := y - 1; searchY >= 0; searchY-- {
						if tree <= trees[searchY][x] {
							return y - searchY
						}
					}

					return y
				}()

				down := func() int {
					for searchY := y + 1; searchY < len(trees); searchY++ {
						if tree <= trees[searchY][x] {
							return searchY - y
						}
					}

					return len(trees) - y - 1
				}()

				return left * right * up * down
			}()

			if result > best {
				best = result
			}
		}
	}

	fmt.Println(best)
}

func main() {
	part1()
	part2()
}
