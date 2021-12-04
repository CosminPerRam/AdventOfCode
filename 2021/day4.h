
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

	for(unsigned drawPosition = 0; wonTable == -1; drawPosition++){ //process drawn numbers until a table has won
		drawnNumber = drawnNumbers[drawPosition];

		for (unsigned b = 0; b < boards.size() && wonTable == -1; b++) { //process all boards until a table has won
			bool found = false;
			for (unsigned i = 0; i < BOARD_SIZE && !found; i++) { //check if there is a drawn number on the board (and stop after finding it)
				for (int j = 0; j < BOARD_SIZE && !found; j++) {
					if (boards[b][i][j] == drawnNumber)
					{
						boards[b][i][j] = -1;
						found = true;
					}
				}
			}

			if (found) { //check if the table has won only if a drawn number was seen
				for (unsigned i = 0; i < BOARD_SIZE && wonTable == -1; i++) { //check boards until one has won (if)
					bool wonH = true, wonV = true; //check horizontal AND vertical separately
					for (int j = 0; j < BOARD_SIZE; j++) {
						if (boards[b][i][j] != -1)
							wonH = false;
						if (boards[b][j][i] != -1)
							wonV = false;
					}

					if (wonH || wonV) //a table won
						wonTable = b;
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

	std::cout << sumUnmarked * drawnNumber << std::endl;
}

void d4p2()
{
	getInput();

	unsigned drawnNumber = 0, lastWonSum = 0;

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
			//^^^ the same as d4p1
			if (found) {
				bool aTableWon = false;
				for (unsigned i = 0; i < BOARD_SIZE && !aTableWon; i++) {
					bool wonH = true, wonV = true;
					for (int j = 0; j < BOARD_SIZE; j++) {
						if (boards[b][i][j] != -1)
							wonH = false;
						if (boards[b][j][i] != -1)
							wonV = false;
					}

					if (wonH || wonV) {
						aTableWon = true;

						if (boards.size() == 1) //last won board
						{
							lastWonSum = 0;
							for (unsigned i = 0; i < BOARD_SIZE; i++) {
								for (int j = 0; j < BOARD_SIZE; j++) {
									if (boards[0][i][j] != -1)
										lastWonSum += boards[0][i][j];
								}
							}
							std::cout << lastWonSum * drawnNumber << std::endl;
						}

						boards.erase(boards.begin() + b);
						b--;
					}
				}
			}
		}
	}
}