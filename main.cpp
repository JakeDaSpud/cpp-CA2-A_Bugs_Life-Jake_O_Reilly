
#include "main.h"

int main() {
    // Variables
    // userInput is string, not int, so I can catch non-int input
    std::string userInput = "-1";

    //std::cout << "DEBUG: Hello, World! START..." << std::endl;

    Board bugBoard;

    /*for (auto &item : bugPtrVector) {
        std::cout << "item&: " << item << "\nbyte size: " << sizeof(item) << std::endl;
    }*/

    do {
        // Display menu options 1-8 to user, then take new input
        printMenu();
        std::cin >> userInput;

        switch (userInput.at(0)) {

            // 1. Initialize Bug Board (load data from file)
            case '1': {
                std::cout << "[1]: Initialising Board..." << std::endl;
                bugBoard.populateBugsFromFile("inputBugs.txt");
                bugBoard.display();

                break;
            }

            // 2. Display all Bugs
            case '2': {
                //bugBoard.display();
                std::cout << "[2]: Printing all Bugs from the Board..." << std::endl;

                if (!bugBoard.getAllBugs(false).empty()) {
                    for (const std::string &currentBug : bugBoard.getAllBugs(false)) {
                        std::cout << currentBug << std::endl;
                    }
                }

                else {
                    std::cout << "Hey! There's no bugs in the board, have you initialised it yet? (Try option [1]!)" << std::endl;
                }

                std::cout << std::endl;

                break;
            }

            // 3. Find a Bug (given an id)
            // bugBoard.findBug(int bugId)
            case '3': {
                std::cout << "[3]: Enter Bug ID to search for:" << std::endl;

                std::string searchingBugId;
                std::cin >> searchingBugId;

                // Valid, ONLY integer input
                if (conversion_utils::trystoi(searchingBugId)) {
                    //std::cout << searchingBugId << std::endl;

                    std::cout << bugBoard.getBugById(conversion_utils::trystoi(searchingBugId));
                }

                else {
                    std::cout << "Error parsing ID...";
                }

                std::cout << std::endl << std::endl;

                break;
            }

            // 4. Tap the Bug Board (causes move all, then fight/eat)
            case '4': {
                std::cout << "[4]: Tapping Board..." << std::endl;

                bugBoard.tap();

                break;
            }

            // 5. Display Life History of all Bugs (path taken)
            // bugBoard.getBugHistory()
            case '5': {
                std::cout << "[5]: Printing every Bug's path history..." << std::endl;

                if (!bugBoard.getAllBugs(false).empty()) {
                    for (const std::string &currentBugHistory : bugBoard.getAllBugHistories()) {
                        std::cout << currentBugHistory << std::endl;
                    }
                }

                else {
                    std::cout << "Hey! There's no Bugs in the board, have you initialised it yet? (Try option [1]!)" << std::endl;
                }

                std::cout << std::endl;

                break;
            }

            //6. Display all Cells listing their Bugs
            case '6': {
                std::cout << "[6]: Printing every Cell's state..." << std::endl;

                for (const std::string &currentBugHistory : bugBoard.getCellState()) {
                    std::cout << currentBugHistory << std::endl;
                }

                std::cout << std::endl;

                break;
            }

            // 7. Run simulation (generates a Tap every second)
            // bugBoard.runSimulation()
            case '7': {
                std::cout << "[7]: Running Simulation..." << std::endl;

                if (!bugBoard.getAllBugs(false).empty()) {
                    bugBoard.runSimulation();
                }

                else {
                    std::cout << "Hey! There's no Bugs in the board, have you initialised it yet? (Try option [1]!)" << std::endl << std::endl;
                }

                break;
            }

            // 8. Exit (write Life History of all Bugs to file)
            case '8': {
                std::cout << "[8]: Exiting and writing Game History..." << std::endl;

                bugBoard.writeGameHistoryToFile();
                break;
            }

            // 9. Start SFML Version
            case '9': {

                // Initialise board for the SFML
                bugBoard.populateBugsFromFile("inputBugs.txt");
                std::cout << "[9]: Starting SFML Version..." << std::endl << std::endl;

                // Run the SFML version
                bugBoard.sfmlMode7();

                break;
            }

            // If the user input isn't 1 - 9
            default: {
                std::cout << "Error: Menu option not recognised." << std::endl << std::endl;

                break;
            }
        }
    } while (conversion_utils::trystoi(userInput) != 8);

    std::cout << "Exiting app, Goodbye!" << std::endl;

    return 0;
}

void printMenu() {
    std::cout << "A Bug's Life: Welcome!\n"
              << "[1] Initialise Board\n"
              << "[2] Display all Bugs\n"
              << "[3] Find a Bug by ID\n"
              << "[4] Tap Board (Progress 1 Game Tick)\n"
              << "[5] Display all Bug History\n"
              << "[6] Display all Board Cell Statuses\n"
              << "[7] Run Simulation\n"
              << "[8] Exit and Save Game History\n"
              << "[9] Start SFML Version\n"
              << "\nEnter a number to choose an item:" << std::endl;
}
