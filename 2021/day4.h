
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#define BOARD_SIZE 5

std::vector<unsigned> drawnNumbers;
std::vector<std::vector<std::vector<unsigned>>> boards;

void getInput() {
	std::ifstream fin("day4.txt");

	unsigned t;
	std::string line;

	std::getline(fin, line);
	for (unsigned i = 0; i < line.length(); i++) {
		if (line[i] == ',')
			line[i] = ' ';
	}
	
	std::istringstream iss(line);
	while (iss >> t)
		drawnNumbers.emplace_back(t);

	while (!fin.eof()) {
		std::vector<std::vector<unsigned>> board;

		for (int i = 0; i < BOARD_SIZE; i++) {
			board.push_back(std::vector<unsigned>());
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				fin >> t;
				board[i].emplace_back(t);
			}
		}
		boards.emplace_back(board);
	}
}

void d4p1()
{
	getInput();

	unsigned drawnNumber = 0, wonTable = -1;

	for(unsigned drawPosition = 0; wonTable == -1; drawPosition++){
		drawnNumber = drawnNumbers[drawPosition];

		for (unsigned b = 0; b < boards.size() && wonTable == -1; b++) {
			bool found = false;
			for (unsigned i = 0; i < BOARD_SIZE && !found; i++) {
				for (int j = 0; j < BOARD_SIZE && !found; j++) {
					if (boards[b][i][j] == drawnNumber)
					{
						boards[b][i][j] = -1;
						found = true;
					}
				}
			}

			if (found) {
				for (unsigned i = 0; i < BOARD_SIZE; i++) {
					bool wonH = true, wonV = true;
					for (int j = 0; j < BOARD_SIZE; j++) {
						if (boards[b][i][j] != -1)
							wonH = false;
						if (boards[b][j][i] != -1)
							wonV = false;
					}

					if (wonH || wonV) {
						wonTable = b;
						break;
					}
				}
			}
		}
	}

	unsigned sumUnmarked = 0;
	for (unsigned i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (boards[wonTable][i][j] != -1)
				sumUnmarked += boards[wonTable][i][j];
		}
	}

	std::cout << sumUnmarked << " " << drawnNumber << std::endl;
	std::cout << sumUnmarked * drawnNumber << std::endl;
}

void d4p2()
{
	getInput();

	unsigned drawnNumber = 0, lastWonSum = 0;
	std::vector<unsigned> wonTables;

	for (unsigned drawPosition = 0; !boards.empty(); drawPosition++) {
		drawnNumber = drawnNumbers[drawPosition];

		for (unsigned b = 0; b < boards.size(); b++) {
			bool found = false;
			for (unsigned i = 0; i < BOARD_SIZE && !found; i++) {
				for (int j = 0; j < BOARD_SIZE && !found; j++) {
					if (boards[b][i][j] == drawnNumber)
					{
						boards[b][i][j] = -1;
						found = true;
					}
				}
			}

			if (found) {
				for (unsigned i = 0; i < BOARD_SIZE; i++) {
					bool wonH = true, wonV = true;
					for (int j = 0; j < BOARD_SIZE; j++) {
						if (boards[b][i][j] != -1)
							wonH = false;
						if (boards[b][j][i] != -1)
							wonV = false;
					}

					if (wonH || wonV) {
						if (boards.size() == 1) //last won board
						{
							lastWonSum = 0;
							for (unsigned i = 0; i < BOARD_SIZE; i++) {
								for (int j = 0; j < BOARD_SIZE; j++) {
									if (boards[0][i][j] != -1)
										lastWonSum += boards[0][i][j];
								}
							}
						}

						boards.erase(boards.begin() + b);
						b--;
						break;
					}
				}
			}
		}
	}

	std::cout << lastWonSum << " " << drawnNumber << std::endl;
	std::cout << lastWonSum * drawnNumber << std::endl;
}