#pragma once

#include <iostream>
#include <fstream>

void d2p1() {
	std::ifstream fin("day2.txt");

	int depth = 0, horizontal = 0;

	std::string instruction;
	unsigned value;
	while (fin >> instruction && fin >> value) {
		if (instruction == "forward")
			horizontal += value;
		else if (instruction == "down")
			depth += value;
		else //up
			depth -= value;
	}

	std::cout << depth * horizontal << std::endl;
}

void d2p2() {
	std::ifstream fin("day2.txt");

	int depth = 0, horizontal = 0, aim = 0;

	std::string instruction;
	unsigned value;
	while (fin >> instruction && fin >> value) {
		if (instruction == "forward")
		{
			horizontal += value;
			depth += aim * value;
		}
		else if (instruction == "down")
			aim += value;
		else //up
			aim -= value;
	}

	std::cout << depth * horizontal << std::endl;
}