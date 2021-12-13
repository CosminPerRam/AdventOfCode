#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

struct point {
    unsigned x, y;
};

struct fold {
    char t;
    unsigned v;
};

std::vector<point> points;
std::vector<fold> folds;

void getInput() {
    std::ifstream fin("day13.txt");
    std::string line;

    while (std::getline(fin, line)) {
        size_t endPos = line.find(',');
        if (endPos != std::string::npos) {
            point p;
            p.x = stoi(line.substr(0, endPos));
            p.y = stoi(line.substr(endPos + 1));

            points.push_back(p);
        }
        else if(!line.empty()) {
            fold f;
            f.t = line[11];
            f.v = stoi(line.substr(13));
            
            folds.push_back(f);
        }
    }
}

void d13p1() {
    getInput();

    fold f = folds[0];
    std::vector<point> uniquePoints;

    for (point p : points) {
        if (f.t == 'y') {
            if (p.y > f.v)
                p.y = f.v - (p.y - f.v);
        }
        else if (f.t == 'x') {
            if (p.x > f.v)
                p.x = f.v - (p.x - f.v);
        }

        bool found = false;
        for (point up : uniquePoints) {
            if (up.x == p.x && up.y == p.y)
            {
                found = true;
                break;
            }
        }

        if (!found)
            uniquePoints.push_back(p);
    }

    std::cout << uniquePoints.size() << std::endl;
}

void d13p2() {
    getInput();

    for (fold f : folds) {
        std::vector<point> uniquePoints;

        for (point p : points) {
            if (f.t == 'y') {
                if (p.y > f.v)
                    p.y = f.v - (p.y - f.v);
            }
            else if (f.t == 'x') {
                if (p.x > f.v)
                    p.x = f.v - (p.x - f.v);
            }

            bool found = false;
            for (point up : uniquePoints) {
                if (up.x == p.x && up.y == p.y)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
                uniquePoints.push_back(p);
        }

        points = uniquePoints;
    }

    unsigned maxX = 0, maxY = 0;

    for (point p : points) {
        if (p.x > maxX)
            maxX = p.x;
        if (p.y > maxY)
            maxY = p.y;
    }

    for (unsigned y = 0; y < maxY + 1; y++) {
        for (unsigned x = 0; x < maxX + 1; x++)
        {
            bool found = false;
            for (point p : points) {
                if (p.x == x && p.y == y)
                {
                    found = true;
                    break;
                }
            }

            if (found)
                std::cout << '#';
            else
                std::cout << '.';
        }
        
        std::cout << std::endl;
    }
}
