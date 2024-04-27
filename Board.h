
#ifndef A_BUGS_LIFE_JAKE_O_REILLY_CA2_BOARD_H
#define A_BUGS_LIFE_JAKE_O_REILLY_CA2_BOARD_H

#include <algorithm>
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
// Functions:
// - Board(int length = 10, int height = 10) [Default will make a 10x10 Board]
// - void tap() [Every Bug uses .move()]
// - void display() [Show board with all alive Bug locations]
// - std::List<std::string> getAllBugs() [Return list of all bugs with Bug.asString]
// - void runSimulation() [Every Bug uses move() every 1 second]
// - void writeGameHistory(std::ofstream fileName)
// - std::string findBug(int bugId)
// - ~Board()

class Board {
private:
    // Fields
    char board[10][10];
    bool initialised = false;

protected:
    std::list<Bug*> allBugs;

public:
    // Default constructor
    Board() {
        //std::cout << "DEBUG: Creating board of size 10x10" << std::endl;

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

    // Board.getBugById(int searchId) / Board->getBugById(int searchId)
    // Search list for specific bug and either return string of bug info, or return "not found" message
    std::string getBugById(const int &searchId);

    // Board.getAllBugs() / Board->getAllBugs()
    std::list<std::string> getAllBugs(const bool &listCellFirst);

    std::list<std::string> getCellState();

    std::list<std::string> getAllBugHistories();

    void populateBugsFromFile(const std::string &fileName);

    void writeGameHistoryToFile();

    virtual ~Board() {}
};


#endif //A_BUGS_LIFE_JAKE_O_REILLY_CA2_BOARD_H
