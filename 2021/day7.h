
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

std::vector<int> crabsPositions;
int maxPosition = 0;

void getInput() {
	std::ifstream fin("day7.txt");
	
	std::string temp;
	int t;
	std::getline(fin, temp);

	std::replace(temp.begin(), temp.end(), ',', ' ');

	std::istringstream iss(temp);
	while (iss >> t)
	{
		crabsPositions.emplace_back(t);
		if (t > maxPosition)
			maxPosition = t;
	}
}

void d7p1() {
	getInput();

	std::vector<int> fuels;
	for (int i = 0; i < maxPosition; i++) {
		fuels.push_back(0);

		for (int c : crabsPositions)
			fuels[i] += std::abs(i - c);
	}

	std::sort(fuels.begin(), fuels.end());

	int min = fuels[0];
	for (int f : fuels)
	{
		if (f < min)
			min = f;
	}

	std::cout << min << std::endl;
}

void d7p2() {
	getInput();

	std::vector<int> fuels;
	for (int i = 0; i < maxPosition; i++) {
		fuels.push_back(0);

		for (int c : crabsPositions) {
			for (unsigned t = 0; t < std::abs(i - c) + 1; t++)
				fuels[i] += t;
		}
	}

	std::sort(fuels.begin(), fuels.end());

	int min = fuels[0];
	for (int f : fuels)
	{
		if (f < min)
			min = f;
	}

	std::cout << min << std::endl;
}
