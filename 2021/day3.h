
#include <iostream>
#include <fstream>
#include <vector>

int binaryToDecimal(std::string n) //from geeksforgeeks.org
{
    std::string num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}

std::vector<std::string> numbers;

void getInput() {
    std::ifstream fin("day3.txt");
    std::string temp;

    while (fin >> temp)
        numbers.push_back(temp);
}

void d3p1()
{
    getInput();

    std::string gamma, epsilon;

    for (int i = 0; i < numbers[0].length(); i++)
    {
        unsigned positiveCount = 0, negativeCount = 0;
        for (const std::string& s : numbers) {
            if (s[i] == '1')
                positiveCount++;
            else
                negativeCount++;
        }

        gamma += (positiveCount > negativeCount) ? '1' : '0';
        epsilon += (positiveCount < negativeCount) ? '1' : '0';
    }

    std::cout << binaryToDecimal(gamma) * binaryToDecimal(epsilon) << std::endl;
}

void d3p2()
{
    getInput();

    std::vector<std::string> copy = numbers;
    std::string temp;

    unsigned oxygenGenerator, COscrubber, maxPosition = numbers[0].length();

    for(unsigned position = 0; numbers.size() > 1 && position < maxPosition; position++) {
        unsigned positiveCount = 0, negativeCount = 0;
        for (const std::string& s : numbers) {
            if (s[position] == '1')
                positiveCount++;
            else
                negativeCount++;
        }

        char c = (positiveCount >= negativeCount) ? '1' : '0';
        for (int i = 0; i < numbers.size(); ) {
            if (numbers[i][position] != c) {
                temp = numbers[i];
                numbers.erase(numbers.begin() + i);
            }
            else
                i++;
        }
    }
    
    oxygenGenerator = (numbers.size() == 1) ? binaryToDecimal(numbers[0]) : binaryToDecimal(temp);

    numbers = copy;
    for (unsigned position = 0; numbers.size() > 1 && position < maxPosition; position++) {
        unsigned positiveCount = 0, negativeCount = 0;
        for (const std::string& s : numbers) {
            if (s[position] == '1')
                positiveCount++;
            else
                negativeCount++;
        }

        char c = (positiveCount >= negativeCount) ? '0' : '1';
        for (int i = 0; i < numbers.size(); ) {
            if (numbers[i][position] != c) {
                temp = numbers[i];
                numbers.erase(numbers.begin() + i);
            }
            else
                i++;
        }
    }

    COscrubber = (numbers.size() == 1) ? binaryToDecimal(numbers[0]) : binaryToDecimal(temp);

    std::cout << oxygenGenerator * COscrubber << std::endl;
}