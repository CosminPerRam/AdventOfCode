
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct vent {
	struct point {
		int x, y;
	};

	point from, to;
};

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

std::vector<vent> allVents;
unsigned maxX = 0, maxY = 0;

void getInput() {
	std::ifstream fin("day5.txt");

	vent tempVent;
	std::string line;
	while (std::getline(fin, line)) {
		replaceAll(line, "->", "");
		replaceAll(line, "  ", " ");
		replaceAll(line, ",", " ");

		std::istringstream iss(line);
		iss >> tempVent.from.x;
		iss >> tempVent.from.y;
		iss >> tempVent.to.x;
		iss >> tempVent.to.y;
		
		allVents.emplace_back(tempVent);

		if (tempVent.to.x > maxX)
			maxX = tempVent.to.x;
		else if (tempVent.to.y > maxY)
			maxY = tempVent.to.y;
		else if (tempVent.from.x > maxX)
			maxX = tempVent.from.x;
		else if (tempVent.from.y > maxY)
			maxY = tempVent.from.y;
	}
}

void d5p1() {
	getInput();

	std::vector<std::vector<unsigned>> table;

	for (unsigned x = 0; x <= maxX; x++) {
		table.push_back(std::vector<unsigned>());
		for (unsigned y = 0; y <= maxY; y++)
			table[x].push_back(0);
	}
	
	for (const vent& fv : allVents) {
		vent v = fv;
		if (v.from.x > v.to.x)
			std::swap(v.to.x, v.from.x);
		if (v.from.y > v.to.y)
			std::swap(v.to.y, v.from.y);

		if (v.from.x == v.to.x || v.from.y == v.to.y) {
			for (unsigned x = v.from.x; x <= v.to.x; x++) {
				for (unsigned y = v.from.y; y <= v.to.y; y++)
					table[x][y]++;
			}
		}
	}
	
	unsigned overlappedPointsCount = 0;
	for (unsigned x = 0; x <= maxX; x++) {
		for (unsigned y = 0; y <= maxY; y++) {
			if (table[x][y] > 1)
				overlappedPointsCount++;
		}
	}

	std::cout << overlappedPointsCount << std::endl;
}

void d5p2() {
	getInput();

	std::vector<std::vector<unsigned>> table;

	for (unsigned x = 0; x <= maxX; x++) {
		table.push_back(std::vector<unsigned>());
		for (unsigned y = 0; y <= maxY; y++)
			table[x].push_back(0);
	}

	for (const vent& fv : allVents) {
		int m = 0;
		if (fv.from.x > fv.to.x && fv.from.y < fv.to.y)
			m = 1;
		else if (fv.from.x < fv.to.x && fv.from.y > fv.to.y)
			m = 2;
		else if (fv.from.x > fv.to.x && fv.from.y > fv.to.y)
			m = 3;

		vent v = fv;
		if (v.from.x > v.to.x)
			std::swap(v.to.x, v.from.x);
		if (v.from.y > v.to.y)
			std::swap(v.to.y, v.from.y);

		if (v.from.x == v.to.x || v.from.y == v.to.y) {
			for (unsigned x = v.from.x; x <= v.to.x; x++) {
				for (unsigned y = v.from.y; y <= v.to.y; y++)
					table[x][y]++;
			}
		} else if (std::abs(fv.from.x - fv.to.x) == std::abs(fv.from.y - fv.to.y)) {
			for (unsigned a = 0; a <= std::abs(fv.from.x - fv.to.x); a++)
			{
				if (m == 0)
					table[fv.from.x + a][fv.from.y + a]++;
				else if (m == 1)
					table[fv.from.x - a][fv.from.y + a]++;
				else if (m == 2)
					table[fv.from.x + a][fv.from.y - a]++;
				else
					table[fv.from.x - a][fv.from.y - a]++;
			}
		}
	}

	unsigned overlappedPointsCount = 0;
	for (unsigned x = 0; x <= maxX; x++) {
		for (unsigned y = 0; y <= maxY; y++) {
			if (table[x][y] > 1)
				overlappedPointsCount++;
		}
	}

	std::cout << overlappedPointsCount << std::endl;
}