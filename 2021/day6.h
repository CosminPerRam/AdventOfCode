
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

void d6p1() { //brute force
	std::vector<unsigned char> timers;
	//input --------------------------
	std::ifstream fin("day6.txt");

	std::string line;
	unsigned t;
	std::getline(fin, line);

	std::replace(line.begin(), line.end(), ',', ' ');

	std::istringstream iss(line);
	while (iss >> t)
		timers.emplace_back(t);
	//--------------------------------
	
	for (unsigned d = 0; d < 80; d++) {
		std::vector<unsigned char> newComers;

		for (unsigned i = 0; i < timers.size(); i++) {
			if (timers[i] == 0)
			{
				timers[i] = 6;
				newComers.emplace_back(8);
			} else
				timers[i]--;
		}

		for (unsigned i = 0; i < newComers.size(); i++)
			timers.emplace_back(newComers[i]);
	}

	std::cout << timers.size() << std::endl;
}

void d6p2() { //optimized
	unsigned long long timersA[9] = { 0 };
	//input --------------------------
	std::ifstream fin("day6.txt");

	std::string line;
	unsigned t;
	std::getline(fin, line);

	std::replace(line.begin(), line.end(), ',', ' ');

	std::istringstream iss(line);
	while (iss >> t)
		timersA[t]++;
	//--------------------------------

	for (unsigned d = 0; d < 256; d++) {
		unsigned long long newComers = timersA[0];

		for (unsigned i = 0; i < 8; i++)
			timersA[i] = timersA[i + 1];

		timersA[6] += newComers;
		timersA[8] = newComers;
	}

	unsigned long long count = 0;
	for (unsigned i = 0; i < 9; i++)
		count += timersA[i];

	std::cout << count << std::endl;
}