
#include "main.h"

int main() {
    // Variables
    // userInput is string, not int, so I can catch non-int input
    std::string userInput = "-1";

    std::cout << "DEBUG: Hello, World! START..." << std::endl;

    Board bugBoard;
    std::vector<Bug*> bugPtrVector;

    for (auto &item : bugPtrVector) {
        std::cout << "item&: " << item << "\nbyte size: " << sizeof(item) << std::endl;
    }

    do {
        // Display menu options 1-8 to user, then take new input
        printMenu();
        std::cin >> userInput;

        switch (userInput.at(0)) {

            // 1. Initialize Bug Board (load data from file)
            case '1': {
                std::cout << "Selected [1] Initialise Board..." << std::endl;
                bugBoard.populateBugsFromFile("inputBugs.txt");
                break;
            }

            // 2. Display all Bugs
            case '2': {
                //bugBoard.display();
                std::cout << "MAIN DEBUG: Printing all bugs from bugBoard..." << std::endl;
                for (const std::string &currentBug : bugBoard.getAllBugs()) {
                    std::cout << currentBug << std::endl;
                }
                break;
            }

            // 3. Find a Bug (given an id)
            // bugBoard.findBug(int bugId)

            // 4. Tap the Bug Board (causes move all, then fight/eat)
            case '4': {
                bugBoard.tap();
                break;
            }

            // 5. Display Life History of all Bugs (path taken)


            //6. Display all Cells listing their Bugs
            // bugBoard.display()

            // 7. Run simulation (generates a Tap every second)
            // bugBoard.runSimulation()

            // 8. Exit (write Life History of all Bugs to file)
            case '8': {
                std::cout << "Option 8: Exit and write game history to a file selected... put the rest of the code in here too..." << std::endl;
                // bugBoard.writeorwhatever("fileOutputName.txt")
                break;
            }

            // If the user input isn't 1 - 8
            default: {
                std::cout << "Error: Menu option not recognised." << std::endl;
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
              << "[8] Exit and Save Bug History\n"
              << "\nEnter a number to choose an item:" << std::endl;
}
