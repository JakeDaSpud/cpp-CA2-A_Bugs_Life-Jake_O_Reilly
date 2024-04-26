#include <fstream>
#include <sstream>
#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"

void Board::display() {
    std::cout << std::endl << "Current Board State:" << std::endl;

    // First update the whole board to show current bug positions
    // Check if there are bugs initialised
    if (!this->allBugs.empty()) {

        // Iterate bugs
        for (Bug* currentBug : allBugs) {
            char boardChar = '-';

            // Check if bug is alive
            if (currentBug->getIsAlive()) {

                if (currentBug->getClass() == "Crawler") {
                    boardChar = 'C';
                }

                else if (currentBug->getClass() == "Hopper") {
                    boardChar = 'H';
                }

                else if (currentBug->getClass() == "Indecisus") {
                    boardChar = 'I';
                }
            }

            // Set dead bug character 'x'
            else {
                boardChar = 'x';
            }

            // Set character on board where that bug is
            board[currentBug->getPosition().first][currentBug->getPosition().second] = boardChar;
        }
    }

    for (int currentColumn = 0; currentColumn < 10; currentColumn++) {
        for (int currentRow = 0; currentRow < 10; currentRow++) {
            std::cout << board[currentRow][currentColumn] << "  ";
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

    Board::display();
}

// Default reading file for instantiating Bugs and storing their pointers into a given vector
void Board::populateBugsFromFile(const std::string &fileName) {
    std::ifstream inputBugFile;
    inputBugFile.open(fileName);

    // Check if file is there
    if (inputBugFile.is_open()) {
        std::string bugFileLine;
        //std::cout << "DEBUG: Reading bug file" << std::endl;

        // Loop through while file has next
        // This is the full bug line being read
        while (std::getline(inputBugFile, bugFileLine)) {
            //std::cout << bugFileLine << std::endl;

            // Adapted using Martin York's SO answer:
            // - https://stackoverflow.com/questions/3910326/c-read-file-line-by-line-then-split-each-line-using-the-delimiter

            std::stringstream linestream(bugFileLine);
            std::string data;

            // Going through current line of file, delim by delim
            // This delim will grab the next ; item
            while (std::getline(linestream, data, ';')) {
                char bugType;
                //int bugId;
                std::string bugId, bugX, bugY, bugDir, bugSize, bugHopLength, bugInterval;

                // Converting data's C or H string to a char
                bugType = data.at(0);

                //std::cout << "bugType: " << bugType << std::endl;

                if (bugType == 'C') {
                    /*linestream >> bugId >> bugX >> bugY >> bugDir >> bugSize*/;
                    std::getline(linestream, bugId, ';');
                    std::getline(linestream, bugX, ';');
                    std::getline(linestream, bugY, ';');
                    std::getline(linestream, bugDir, ';');
                    std::getline(linestream, bugSize, ';');

                    // Instantiate Crawler
                    Crawler *newCrawler = new Crawler(std::stoi(bugId), std::pair<int, int>(std::stoi(bugX), std::stoi(bugY)), conversion_utils::stodir(bugDir), std::stoi(bugSize));
                    //std::cout << "newCrawler made: " << newCrawler->asString() << std::endl;

                    // Add ptr to vector
                    this->allBugs.push_back(newCrawler);
                    std::cout << "Added Crawler..." << std::endl;
                }

                else if (bugType == 'H') {

                    std::getline(linestream, bugId, ';');
                    std::getline(linestream, bugX, ';');
                    std::getline(linestream, bugY, ';');
                    std::getline(linestream, bugDir, ';');
                    std::getline(linestream, bugSize, ';');
                    std::getline(linestream, bugHopLength, ';');

                    // Instantiate Hopper
                    Hopper *newHopper = new Hopper(std::stoi(bugId), std::pair<int, int>(std::stoi(bugX), std::stoi(bugY)), conversion_utils::stodir(bugDir), std::stoi(bugSize), std::stoi(bugHopLength));
                    //std::cout << "newHopper made: " << newHopper->asString() << std::endl;

                    // Add ptr to vector
                    this->allBugs.push_back(newHopper);
                    std::cout << "Added Hopper..." << std::endl;
                }

                /* Custom Bug
                else if (.at(0) == 'I') {
                    // Instantiate Indecisus

                    // Add ptr to vector
                }
                 */
            }
        }

        // Close file after reading
        inputBugFile.close();
    }

        // Error, can't find input file
    else {
        std::cout << "Error: Can't read input file." << std::endl;
    }
}

void Board::runSimulation() {}

// Return all bugs in this board as a list of strings, instead of their Bug objects
std::list<std::string> Board::getAllBugs(const bool &listCellFirst = false) {
    std::list<std::string> bugListOut;

    // Original function didn't care about cells being first, now I must check if the user is printing by cell or just all bugs!
    for (Bug* currentBug : this->allBugs) {
        std::string prefix = "";

        // If listCellFirst formatting is passed as true, we'll concat the cell position first!
        if (listCellFirst) {
            prefix = " (" + std::to_string(currentBug->getPosition().first) + ", ";
            prefix += std::to_string(currentBug->getPosition().second) + "): ";
        }

        bugListOut.push_back(prefix + currentBug->asString());
    }

    return bugListOut;
}

std::list<std::string> Board::getCellState() {
    std::list<std::string> cellListOut;

    // This temp list is instantiated in the first layer of the function because we probably wouldn't be printing the
    // cell state without putting bugs in first
    std::list<Bug*> bugsToBeConcat;

    for (int currentY = 0; currentY < 10; currentY++) {

        for (int currentX = 0; currentX < 10; currentX++) {

            // This will be added to cellListOut, it will say the coordinate and the cell state
            // Add current coordinate to output
            std::string cellData = "[" + std::to_string(currentX) + ", " + std::to_string(currentY) + "]: ";

            // this means the cell is empty, concat empty
            if (board[currentX][currentY] == '-') {
                cellData += "empty";
            }

            // the cell is NOT '-', so there is a bug (in any state) here
            else {

                for (Bug* tempBug : allBugs) {

                    //std::cout << "tempBug: " + tempBug->asString() << std::endl;

                    // Add all bugs to the temp toBeDealtWith list with the current coords
                    if (tempBug->getPosition().first == currentX && tempBug->getPosition().second == currentY) {
                        std::string alive = (tempBug->getIsAlive()) ? "Yes" : "No";

                        cellData += tempBug->asString() + " alive[" + alive + "]; ";
                    }

                    // Go through list of temp bugs, concatting them to the cellData like Bug->asString() + ";"
                    //for (Bug* tempBug : bugsToBeConcat)
                }
            }

            // Adding the current finished cellData to the output list
            cellListOut.push_back(cellData);
        }

    }

    return cellListOut;
}

// Return all bugs in this board as a list of strings, instead of their Bug objects
std::list<std::string> Board::getAllBugHistories() {
    std::list<std::string> bugHistoryListOut;

    // Iterate through all bugs
    for (Bug* currentBug : this->allBugs) {
        std::string temp;

        temp = "[" + std::to_string(currentBug->getId()) + "] " + currentBug->getClass();

        // Iterate through currentBug's list of pair<int, int>s
        for (std::pair<int, int> path : currentBug->getPath()) {

            temp += " (" + std::to_string(path.first) + ", ";
            temp += std::to_string(path.second) + ");";
        }

        bugHistoryListOut.push_back(temp);
    }

    return bugHistoryListOut;
}

// Compare all bugs in the board until you find the same id, or leave the default message
std::string Board::getBugById(const int &searchId) {
    std::string bugDataOut = "Bug not found on the board!";

    for (Bug* currentBug : this->allBugs) {
        if (currentBug->getId() == searchId) {
            bugDataOut = "Found Bug [" + std::to_string(searchId) + "]: ";
            bugDataOut += currentBug->asString();
            break;
        }
    }

    return bugDataOut;
}
