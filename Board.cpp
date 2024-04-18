
#include "Board.h"

void Board::display() {
    std::cout << std::endl << "Current Board State:" << std::endl;
    for (int currentColumn = 0; currentColumn < 10; currentColumn++) {
        for (int currentRow = 0; currentRow < 10; currentRow++) {
            std::cout << board[currentColumn][currentRow] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Board::tap() {
    std::cout << "DEBUG: Board::tap()" << std::endl;

    for (Bug* bug: allBugs) {
        std::move(bug);
    }
}

void Board::runSimulation() {}