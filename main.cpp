
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
    } while (conversion_utils::trystoi(userInput) != 8);

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
        // This is the full bug line being read
        while (std::getline(inputBugFile, bugFileLine)) {
            std::cout << bugFileLine << std::endl;

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

                std::cout << "bugType: " << bugType << std::endl;

                if (bugType == 'C') {
                    /*linestream >> bugId >> bugX >> bugY >> bugDir >> bugSize*/;
                    std::getline(linestream, bugId, ';');
                    std::getline(linestream, bugX, ';');
                    std::getline(linestream, bugY, ';');
                    std::getline(linestream, bugDir, ';');
                    std::getline(linestream, bugSize, ';');

                    // Instantiate Crawler
                    Crawler *newCrawler = new Crawler(std::stoi(bugId), std::pair<int, int>(std::stoi(bugX), std::stoi(bugY)), conversion_utils::stodir(bugDir), std::stoi(bugSize));
                    std::cout << "newCrawler made: " << newCrawler->asString() << std::endl;

                    // Add ptr to vector
                    bugVector.push_back(newCrawler);
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
                    std::cout << "newHopper made: " << newHopper->asString() << std::endl;

                    // Add ptr to vector
                    bugVector.push_back(newHopper);
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

        //DEBUG print out all bugs ////////////////////////////////////////////// i was here checkpoint ! ! !!!
        /*for (auto item: bugVector) {
            item->asString();
        }*/

        // For formatting purposes, don't want the outputs touching!
        std::cout << std::endl;
    }

    // Error, can't find input file
    else {
        std::cout << "Error: Can't read input file." << std::endl;
    }
}
