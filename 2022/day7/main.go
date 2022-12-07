package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Directory struct {
	directories map[string]*Directory
	files       map[string]int
	parent      *Directory
}

func part1() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	defer readFile.Close()

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	root := Directory{}
	root.parent = &root
	root.directories = make(map[string]*Directory)
	root.files = make(map[string]int)

	currentFolder := &root

	for fileScanner.Scan() {
		line := fileScanner.Text()

		splits := strings.Split(line, " ")

		switch splits[0] {
		case "dir":
			dirToAdd := Directory{}
			dirToAdd.parent = currentFolder
			dirToAdd.directories = make(map[string]*Directory)
			dirToAdd.files = make(map[string]int)

			currentFolder.directories[splits[1]] = &dirToAdd
		case "$":
			switch splits[1] {
			case "cd":
				switch splits[2] {
				case "/":
					currentFolder = &root
				case "..":
					currentFolder = currentFolder.parent
				default:
					currentFolder = currentFolder.directories[splits[2]]
				}

			}
		default:
			num, err := strconv.Atoi(splits[0])

			if err != nil {
				fmt.Println(err)
			}

			currentFolder.files[splits[1]] = num
		}
	}

	// recursive anonymous function YEP
	var getFromFolder func(dir *Directory) (int, int)

	getFromFolder = func(dir *Directory) (int, int) {
		currentDirSum := 0
		currentDirAnswerSum := 0

		for _, value := range dir.files {
			currentDirSum += value
		}

		for _, value := range dir.directories {
			sum, ansSum := getFromFolder(value)

			currentDirSum += sum
			currentDirAnswerSum += ansSum
		}

		if currentDirSum <= 100000 {
			currentDirAnswerSum += currentDirSum
		}

		return currentDirSum, currentDirAnswerSum
	}

	_, ansSum := getFromFolder(&root)

	fmt.Println(ansSum)
}

func part2() {
	readFile, err := os.Open("input")

	if err != nil {
		fmt.Println(err)
	}

	defer readFile.Close()

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)

	root := Directory{}
	root.parent = &root
	root.directories = make(map[string]*Directory)
	root.files = make(map[string]int)

	currentFolder := &root

	for fileScanner.Scan() {
		line := fileScanner.Text()

		splits := strings.Split(line, " ")

		switch splits[0] {
		case "dir":
			dirToAdd := Directory{}
			dirToAdd.parent = currentFolder
			dirToAdd.directories = make(map[string]*Directory)
			dirToAdd.files = make(map[string]int)

			currentFolder.directories[splits[1]] = &dirToAdd
		case "$":
			switch splits[1] {
			case "cd":
				switch splits[2] {
				case "/":
					currentFolder = &root
				case "..":
					currentFolder = currentFolder.parent
				default:
					currentFolder = currentFolder.directories[splits[2]]
				}

			}
		default:
			num, err := strconv.Atoi(splits[0])

			if err != nil {
				fmt.Println(err)
			}

			currentFolder.files[splits[1]] = num
		}
	}

	var getFromFolder func(dir *Directory) int

	getFromFolder = func(dir *Directory) int {
		currentDirSum := 0

		for _, value := range dir.files {
			currentDirSum += value
		}

		for _, value := range dir.directories {
			sum := getFromFolder(value)

			currentDirSum += sum
		}

		return currentDirSum
	}

	sum := getFromFolder(&root)

	needToFreeUp := 30000000 - (70000000 - sum)

	var getBiggestValidSize func(dir *Directory, minSize int) (int, int)

	getBiggestValidSize = func(dir *Directory, minSize int) (int, int) {
		currentDirSum := 0
		min := 70000000

		for _, value := range dir.files {
			currentDirSum += value
		}

		for _, value := range dir.directories {
			sum, localMin := getBiggestValidSize(value, minSize)

			if localMin < min && localMin >= minSize {
				min = localMin
			}

			currentDirSum += sum
		}

		if currentDirSum < min && currentDirSum >= minSize {
			min = currentDirSum
		}

		return currentDirSum, min
	}

	_, ans := getBiggestValidSize(&root, needToFreeUp)

	fmt.Println(ans)
}

func main() {
	part1()
	part2()
}
