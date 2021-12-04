#pragma once

#include <iostream>
#include <fstream>
#include <vector>

void d1p1() {
	std::ifstream fin("day1.txt");

	unsigned n, nn, count = 0;
	fin >> n;

	while (!fin.eof())
	{
		fin >> nn;
		if (nn > n)
			count++;
		n = nn;
	}

	std::cout << count << std::endl;
}

void d1p2() {
	std::ifstream fin("day1.txt");

	unsigned count = 0, a, b, t;
	std::vector<unsigned> ns;

	while (!fin.eof()) {
		fin >> t;
		ns.emplace_back(t);
	}

	a = ns[0] + ns[1] + ns[2];
	for (int i = 1; i < ns.size() - 3; i++) {
		b = ns[i] + ns[i + 1] + ns[i + 2];
		if (b > a)
			count++;
		a = b;
	}

	std::cout << count << std::endl;
}