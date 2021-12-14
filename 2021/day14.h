#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>

void d14p1() {
    struct rule {
        std::string between;
        char put;

        rule(std::string between, char put) {
            this->between = between;
            this->put = put;
        }
    };

    std::string thePolymer;
    std::vector<rule> rules;

    std::ifstream fin("day14e.txt");
    std::string line;

    std::getline(fin, thePolymer);
    std::getline(fin, line);

    while (std::getline(fin, line))
        rules.emplace_back(rule(line.substr(0, 2), line[6]));

    for (unsigned step = 0; step < 10; step++) {
        for (unsigned p = 0; p < thePolymer.length() - 1; p++) {
            for (const rule& r : rules) {
                if (thePolymer.substr(p, 2) == r.between)
                {
                    thePolymer.insert(p + 1, 1, r.put);
                    p++;
                    break;
                }
            }
        }
    }

    std::vector<std::pair<char, unsigned>> occurences;
    for (unsigned p = 0; p < thePolymer.length(); p++) {
        bool found = false;
        for (unsigned i = 0; i < occurences.size(); i++) {
            if (occurences[i].first == thePolymer[p])
            {
                occurences[i].second++;
                found = true;
            }
        }

        if (!found)
            occurences.emplace_back(thePolymer[p], 1);
    }

    std::sort(occurences.begin(), occurences.end(), [](auto& left, auto& right) {
        return left.second < right.second;
        });

    std::cout << occurences[occurences.size() - 1].second - occurences[0].second << std::endl;
}

void d14p2() {
    std::string thePolymer;

    std::ifstream fin("day14e.txt");
    std::string line;

    std::getline(fin, thePolymer);
    std::getline(fin, line);

    unsigned long long combs[676] = { 0 }; //combinations count
    unsigned long long rules[676] = { 0 }; //rules letter
    unsigned long long lolz[26] = { 0 }; //letter count

    for (unsigned i = 0; i < thePolymer.length(); i++)
        lolz[thePolymer[i] - 'A']++; //add the current polymer's letters

    for (unsigned i = 0; i < thePolymer.length() - 1; i++)
        combs[(thePolymer[i] - 'A') * 26 + thePolymer[i + 1] - 'A']++; //add the current combinations

    while (std::getline(fin, line))
        rules[(line[0] - 'A') * 26 + line[1] - 'A'] = line[6]; //create the rules

    for (unsigned step = 0; step < 40; step++) {
        unsigned long long newCombs[676] = { 0 };

        for (unsigned c = 0; c < 676; c++) {
            if (combs[c] > 0) {
                unsigned long long toAdd = (rules[c] - 'A');

                newCombs[c / 26 * 26 + toAdd] += combs[c]; //left
                newCombs[toAdd * 26 + c % 26] += combs[c]; //right

                lolz[toAdd] += combs[c];
            }
        }

        for (unsigned c = 0; c < 676; c++)
            combs[c] = newCombs[c];
    }

    unsigned long long max = 0;
    unsigned long long min = ULLONG_MAX;

    for (unsigned l = 0; l < 26; l++)
    {
        if (lolz[l] > 0) {
            if (lolz[l] > max)
                max = lolz[l];
            if (lolz[l] < min)
                min = lolz[l];
        }
    }

    std::cout << max - min << std::endl;
}