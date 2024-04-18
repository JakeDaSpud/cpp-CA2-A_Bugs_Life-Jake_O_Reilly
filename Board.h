
#ifndef A_BUGS_LIFE_JAKE_O_REILLY_CA2_BOARD_H
#define A_BUGS_LIFE_JAKE_O_REILLY_CA2_BOARD_H

#include <list>
#include <string>
#include <vector>
#include "Bug.h"

// The board will:
// - Be where Bugs are stored (Hoppers, Crawlers, Indecisus)
// - Be a 10x10 int[][] grid
// - Send "Win" condition when there is 1 alive bug remaining
// - Make 2 Bugs on the same cell .fight()
// - Make all bugs use .move() in .tap() and .runSimulation()
//

// Board
// Fields:
// - int[][] state
// - List<Bug*> allBugs
// - List<Bug*> aliveBugs
// Functions:
// - Board(int length = 10, int height = 10) [Default will make a 10x10 Board]
// - void tap() [Every Bug uses .move()]
// - void display() [Show board with all alive Bug locations]
// - void displayAllBugs()
// - std::List<std::string> getAliveBugs() [Return list of all alive bugs with Bug.asString]
// - void runSimulation() [Every Bug uses move() every 1 second]
// - void writeGameHistory(std::ofstream fileName)
// - std::string findBug(int bugId)
// - ~Board()

class Board {
private:
    // Fields
    std::list<Bug*> allBugs;
    char board[10][10];

public:
    // Default constructor
    Board() {
        std::cout << "DEBUG: Creating board of size 10x10" << std::endl;

        for (int currentColumn = 0; currentColumn < 10; currentColumn++) {
            for (int currentRow = 0; currentRow < 10; currentRow++) {
                board[currentColumn][currentRow] = '-';
            }
        }
    };

    // Board.tap() / Board->tap()
    // public
    // All ALIVE (assumption) Bugs will perform .move()
    // After .move(), all Bug positions will be compared to see if any are the same: this means they are on the same cell
    // If two Bugs are on the same cell, perform .fight(Bug *bug1, Bug *bug2)
    void tap();

    // Board.runSimulation() / Board->runSimulation()
    // public
    // Every 1 second, run Board.tap() / Board->tap()
    void runSimulation();

    // Board.display() / Board->display()
    // public
    // Print out a 10x10 grid, where each cell is either:
    // - H: Hopper
    // - C: Crawler
    // - I: Indecisus
    // - -: Empty / Null / Dead Bug
    void display();

    // Board.fight() /  Board->fight()
    // private
    // @param: Bug *bug1, Bug *bug2
    // Double pointer function to compare
    // Check location of all Bugs, if they
    void fight();


    std::list<std::string> getAliveBugs();

    virtual ~Board() {}
};


#endif //A_BUGS_LIFE_JAKE_O_REILLY_CA2_BOARD_H
