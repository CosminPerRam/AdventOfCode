#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

struct batch {
    std::vector<std::string> signals;
    std::vector<std::string> digits;

    batch(std::vector<std::string> signals, std::vector<std::string> digits) {
        this->signals = signals;
        this->digits = digits;
    }
};

std::vector<batch> batches;

void getInput() {
    std::ifstream fin("day8.txt");
    std::string line, temp;

    while (std::getline(fin, line)) {
        unsigned endPos = line.find('|');

        std::vector<std::string> signals;
        std::vector<std::string> digits;

        std::istringstream iss(line.substr(0, endPos - 1));
        while (iss >> temp)
            signals.emplace_back(temp);

        iss = std::istringstream(line.substr(endPos + 1));
        while (iss >> temp)
            digits.emplace_back(temp);

        batches.emplace_back(signals, digits);
    }
}

void d8p1() {
    getInput();

    unsigned appears = 0;

    for (const batch& b : batches) {
        for (const std::string& s : b.digits) {
            if (s.length() == 2 || s.length() == 4 || s.length() == 3 || s.length() == 7)
                appears++;
        }
    }

    std::cout << appears << std::endl;
}

void d8p2() {
    getInput();


}