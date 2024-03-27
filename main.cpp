
#include "main.h"

int main() {
    // Variables
    // userInput is string, not int, so I can catch non-int input
    std::string userInput = "-1";

    std::cout << "DEBUG: Hello, World! START..." << std::endl;

    // temp Bugs
    /*Crawler c1 = Crawler(1, std::pair(0, 0), direction::NORTH, 1);
    Hopper h1 = Hopper(2, std::pair(1, 1), direction::SOUTH, 2, 1);

    Crawler *c1Ptr = &c1;
    Hopper *h1Ptr = &h1;*/

    std::vector<Bug*> bugPtrVector;

    for (auto &item : bugPtrVector) {
        std::cout << "item&: " << item << "\nbyte size: " << sizeof(item) << std::endl;
    }

    do {
        // Display menu options 1-8 to user, then take new input
        printMenu();
        std::cin >> userInput;

        switch (userInput.at(0)) {
            case '1':
                std::cout << "Selected [1] Initialise Board..." << std::endl;
                populateBugsFromFile(bugPtrVector, "inputBugs.txt");

                break;

            default:
                std::cout << "Error: Menu option not recognised." << std::endl;
                break;
        }
    } while (trystoi(userInput) != 8);

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

// Default reading file for instantiating Bugs and storing their pointers into a given vector
void populateBugsFromFile(std::vector<Bug*> &bugVector, std::string fileName) {
    std::ifstream inputBugFile;
    inputBugFile.open(fileName);

    // Check if file is there
    if (inputBugFile.is_open()) {
        std::string bugFileLine;
        std::cout << "DEBUG: Reading bug file" << std::endl;

        // Loop through while file has next
        while (std::getline(inputBugFile, bugFileLine)) {
            std::cout << bugFileLine << std::endl;
        }

        // Close file after reading
        inputBugFile.close();
    }

    // Error, can't find input file
    else {
        std::cout << "Error: Can't read input file." << std::endl;
    }
}

int trystoi(const std::string &stoiString) {

    try {
        // If stoi works, it will return an int from the string
        return stoi(stoiString);
    }

    // exception / error gets put into &e, it is when stoi doesn't work and there's no int in the string
    catch (const std::invalid_argument &e) {
        std::cerr << "std::invalid_argument error from: " << e.what() << std::endl;
        std::cout << "Returning to menu...\n" << std::endl;

        // Return -1 when there's no int in the string input, this means the main menu will continue the loop!
        return -1;
    }
}