#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#define MSIZE 10

unsigned map[MSIZE][MSIZE];

void getInput() {
    std::ifstream fin("day11.txt");
    char n;

    for (unsigned i = 0; i < MSIZE; i++) {
        for (unsigned j = 0; j < MSIZE; j++) {
            fin >> n;
            map[i][j] = n - '0';
        }
    }
}

void d11p1() {
    getInput();

    unsigned flashes = 0;
    for (unsigned s = 0; s < 100; s++) {
        for (unsigned i = 0; i < MSIZE; i++) {
            for (unsigned j = 0; j < MSIZE; j++)
                map[i][j]++;
        }

        bool flashed[MSIZE][MSIZE] = { false };

        bool ok;
        do {
            ok = true;
            for (int i = 0; i < MSIZE; i++) {
                for (int j = 0; j < MSIZE; j++) {
                    if (map[i][j] > 9 && !flashed[i][j]) {
                        if (i - 1 >= 0) {
                            if (j - 1 >= 0)
                                map[i - 1][j - 1]++;

                            map[i - 1][j]++;

                            if (j + 1 < MSIZE)
                                map[i - 1][j + 1]++;
                        }

                        if (j - 1 >= 0)
                            map[i][j - 1]++;

                        map[i][j]++;

                        if (j + 1 < MSIZE)
                            map[i][j + 1]++;

                        if (i + 1 < MSIZE) {
                            if (j - 1 >= 0)
                                map[i + 1][j - 1]++;

                            map[i + 1][j]++;

                            if (j + 1 < MSIZE)
                                map[i + 1][j + 1]++;
                        }

                        flashed[i][j] = true;
                        ok = false;
                    }
                }
            }
        } while (!ok);

        for (int i = 0; i < MSIZE; i++) {
            for (int j = 0; j < MSIZE; j++) {
                if (flashed[i][j]) {
                    map[i][j] = 0;
                    flashes++;
                }
            }
        }
    }

    std::cout << flashes << std::endl;
}

void d11p2() {
    getInput();

    unsigned step = 0, sum;
    do {
        sum = 0;
        for (unsigned i = 0; i < MSIZE; i++) {
            for (unsigned j = 0; j < MSIZE; j++)
                map[i][j]++;
        }

        bool flashed[MSIZE][MSIZE] = { false };

        bool ok;
        do {
            ok = true;
            for (int i = 0; i < MSIZE; i++) {
                for (int j = 0; j < MSIZE; j++) {
                    if (map[i][j] > 9 && !flashed[i][j]) {
                        if (i - 1 >= 0) {
                            if (j - 1 >= 0)
                                map[i - 1][j - 1]++;

                            map[i - 1][j]++;

                            if (j + 1 < MSIZE)
                                map[i - 1][j + 1]++;
                        }

                        if (j - 1 >= 0)
                            map[i][j - 1]++;

                        map[i][j]++;

                        if (j + 1 < MSIZE)
                            map[i][j + 1]++;

                        if (i + 1 < MSIZE) {
                            if (j - 1 >= 0)
                                map[i + 1][j - 1]++;

                            map[i + 1][j]++;

                            if (j + 1 < MSIZE)
                                map[i + 1][j + 1]++;
                        }

                        flashed[i][j] = true;
                        ok = false;
                    }
                }
            }
        } while (!ok);

        for (int i = 0; i < MSIZE; i++) {
            for (int j = 0; j < MSIZE; j++) {
                if (flashed[i][j]) {
                    map[i][j] = 0;
                }
                sum += map[i][j];
            }
        }
        step++;
    } while (sum != 0);

    std::cout << step << std::endl;
}