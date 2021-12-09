#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

struct point {
    unsigned value;
    bool visited = false;

    point(unsigned value) : value(value) {};
};

std::vector<std::vector<point>> map;
unsigned height = 0, width;

void getInput() {
    std::ifstream fin("day9.txt");
    std::string line;

    while (std::getline(fin, line)) {
        map.push_back(std::vector<point>());
        width = line.size();

        for (char c : line)
            map[height].emplace_back(c - '0');

        height++;
    }
}

void d9p1() {
    getInput();

    unsigned sum = 0;

    for (unsigned x = 0; x < height; x++) {
        for (unsigned y = 0; y < width; y++)
        {
            bool isLowPoint = true;

            if (x + 1 < height)
                if (map[x + 1][y].value <= map[x][y].value)
                    isLowPoint = false;
            if (y + 1 < width)
                if (map[x][y + 1].value <= map[x][y].value)
                    isLowPoint = false;
            if (x != 0)
                if (map[x - 1][y].value <= map[x][y].value)
                    isLowPoint = false;
            if (y != 0)
                if (map[x][y - 1].value <= map[x][y].value)
                    isLowPoint = false;

            if(isLowPoint) {
                std::cout << "Found low point, v = " << map[x][y].value << " p = " << x << "," << y << std::endl;
                sum += map[x][y].value + 1;
            }
        }
    }

    std::cout << sum << std::endl;
}

unsigned basinSize(int x, int y) {
    if (x < 0 || y < 0 || x == height || y == width)
        return 0;
    if (map[x][y].visited)
        return 0;
    if (map[x][y].value == 9)
        return 0;

    map[x][y].visited = true;

    return 1 + basinSize(x + 1, y) + basinSize(x - 1, y) + basinSize(x, y + 1) + basinSize(x, y - 1);
}

void d9p2() {
    getInput();

    std::vector<unsigned> basins;

    for (unsigned x = 0; x < height; x++) {
        for (unsigned y = 0; y < width; y++)
        {
            unsigned v = basinSize(x, y);
            if (v != 0)
                basins.push_back(v);
        }
    }

    std::sort(basins.begin(), basins.end());

    std::cout << basins[basins.size() - 3] * basins[basins.size() - 2] * basins[basins.size() - 1] << std::endl;
}