#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

std::vector<std::string> batch;

void getInput() {
    std::ifstream fin("day10.txt");
    std::string line, temp;

    while (fin >> line)
        batch.push_back(line);
}

void d10p1() {
    getInput();

    std::vector<char> expected;
    unsigned score = 0;

    for (std::string s : batch)
    {
        bool corrupted = false;
        for (unsigned p = 0; p < s.length() && !corrupted; p++) {
            if (s[p] == '(')
                expected.emplace_back(')');
            else if (s[p] == '[')
                expected.emplace_back(']');
            else if (s[p] == '{')
                expected.emplace_back('}');
            else if (s[p] == '<')
                expected.emplace_back('>');
            else { //if (s[p] == ')' || s[p] == ']' || s[p] == '}' || s[p] == '>')
                if (expected.back() == s[p])
                    expected.pop_back();
                else
                {
                    corrupted = true;

                    if (s[p] == ')')
                        score += 3;
                    else if (s[p] == ']')
                        score += 57;
                    else if (s[p] == '}')
                        score += 1197;
                    else if (s[p] == '>')
                        score += 25137;
                }
            }
        }
    }

    std::cout << score << std::endl;
}

void d10p2() {
    getInput();
    
    std::vector<unsigned long long> scores;

    for (std::string s : batch)
    {
        std::vector<char> expected;
        unsigned long long score = 0;
        bool corrupted = false;

        for (unsigned p = 0; p < s.length() && !corrupted; p++) {
            if (s[p] == '(')
                expected.emplace_back(')');
            else if (s[p] == '[')
                expected.emplace_back(']');
            else if (s[p] == '{')
                expected.emplace_back('}');
            else if (s[p] == '<')
                expected.emplace_back('>');
            else { //if (s[p] == ')' || s[p] == ']' || s[p] == '}' || s[p] == '>')
                if (expected.back() == s[p])
                    expected.pop_back();
                else
                    corrupted = true;
            }
        }

        if (!corrupted && expected.size() > 0) {
            for (unsigned p = expected.size(); p > 0; p--) {
                char c = expected[p - 1];
                score *= 5;

                if (c == ')')
                    score += 1;
                else if (c == ']')
                    score += 2;
                else if (c == '}')
                    score += 3;
                else //if(c == '>')
                    score += 4;
            }

            scores.push_back(score);
        }
    }

    std::nth_element(scores.begin(), scores.begin() + scores.size() / 2, scores.end()); //thanks simondvt (reddit)

    std::cout << scores[scores.size() / 2] << std::endl;
}