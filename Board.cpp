#include <fstream>
#include <sstream>
#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Indecisus.h"

void Board::display() {
    std::cout << std::endl << "Current Board State:" << std::endl;

    // Refresh board to be filled with characters
    // This is so the previous move's characters won't "ghost" on the display
    for (int currentColumn = 0; currentColumn < 10; currentColumn++) {
        for (int currentRow = 0; currentRow < 10; currentRow++) {
            board[currentColumn][currentRow] = '-';
        }
    }

    // First update the whole board to show current bug positions
    // Check if there are bugs initialised
    if (!this->allBugs.empty()) {

        // Iterate bugs
        for (Bug* currentBug : allBugs) {
            char boardChar = '-';

            // Check if bug is alive
            if (!currentBug->getIsAlive()) {
                // Set dead bug character 'x'
                boardChar = 'x';
            }

            else if (currentBug->getClass() == "Crawler") {
                boardChar = 'C';
            }

            else if (currentBug->getClass() == "Hopper") {
                boardChar = 'H';
            }

            else if (currentBug->getClass() == "Indecisus") {
                boardChar = 'I';
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
    //std::cout << "DEBUG: Board::tap()" << std::endl;

    for (Bug* bug: allBugs) {
        if (bug->getIsAlive()) {
            bug->move();
        }
    }

    fight();

    Board::display();
}

// Default reading file for instantiating Bugs and storing their pointers into a given vector
void Board::populateBugsFromFile(const std::string &fileName) {

    // Check if the board has already been initialised
    if (!initialised) {

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
                    } else if (bugType == 'H') {

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
                    } else if (bugType == 'I') {

                        std::getline(linestream, bugId, ';');
                        std::getline(linestream, bugX, ';');
                        std::getline(linestream, bugY, ';');
                        std::getline(linestream, bugDir, ';');
                        std::getline(linestream, bugSize, ';');
                        std::getline(linestream, bugInterval, ';');

                        // Instantiate
                        Indecisus *newIndecisus = new Indecisus(std::stoi(bugId), std::pair<int, int>(std::stoi(bugX), std::stoi(bugY)), conversion_utils::stodir(bugDir), std::stoi(bugSize), std::stoi(bugInterval));

                        // Add ptr to vector
                        this->allBugs.push_back(newIndecisus);
                        std::cout << "Added Indecisus..." << std::endl;
                    }
                }
            }

            // Close file after reading
            inputBugFile.close();

            initialised = true;
        }

            // Error, can't find input file
        else {
            std::cout << "Error: Can't read input file." << std::endl;
        }
    }

    else {
        std::cout << "Board already initialised with Bugs!" << std::endl;
    }
}

// Run tap() every 1 second
void Board::runSimulation() {

    int deltaTime = 0;
    int boardTurn = 0;

    // While there's more than 1 bug alive, keep tapping and waiting
    while (getAliveBugCount() > 1) {
        boardTurn++;
        std::cout << "Turn " << boardTurn << std::endl;

        tap();
        sleep(deltaTime);
    }

    Bug *winnerBug;

    // Find winner (last bug alive)
    for (Bug* currentBug : allBugs) {
        if (currentBug->getIsAlive()) {
            winnerBug = currentBug;
        }
    }

    // One alive bug is the winner, print them out and leave function.
    std::cout << "Winner!: " << winnerBug->asString() << std::endl << std::endl;
}

int Board::getAliveBugCount() {
    int result = 0;

    for (Bug* currentBug : allBugs) {
        if (currentBug->getIsAlive()) {
            result++;
        }
    }

    return result;
}

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

// Find all bugs on the same cell, then make them compare size, biggest adds the loser's size to its own and loser dies
void Board::fight() {

    std::map<std::pair<int, int>, std::list<Bug*>> cell_bugs_Map;

    // 1. Find all bugs on the same cell

    // This is kind of like Two Sum
    // Bug doing the comparison, go through all Bugs
    for (Bug* currentBug : allBugs) {

        // Make sure we're only using alive Bugs
        if (currentBug->getIsAlive()) {

            // Bug being compared, all Bugs after nextBug, that AREN'T currentBug
            for (Bug* nextBug : allBugs) {

                // Check if nextBug isn't currentBug, and compare positions
                if (currentBug != nextBug && currentBug->getPosition() == nextBug->getPosition()) {
                    //std::cout << "DEBUG: Found two bugs on same cell:" << currentBug->asString() << std::endl << " and " << std::endl << nextBug->asString() << std::endl;

                    // IF ENTRY DOESN'T EXIST: Create new entry for the cell-Bugs to the map
                    if (cell_bugs_Map[currentBug->getPosition()].empty()) {
                        // Adding the new entry
                        cell_bugs_Map[currentBug->getPosition()] = std::list<Bug*> {currentBug, nextBug};

                        // Debug printing out the new entry
                        //std::cout << "DEBUG: Made new Map entry for position: " << currentBug->getPosition().first << ", " << currentBug->getPosition().second << std::endl;

                        /*std::cout << "DEBUG: Bugs at this position:" << std::endl;
                        for (Bug* bugToPrint: cell_bugs_Map[currentBug->getPosition()]) {
                            std::cout << bugToPrint->asString() << std::endl;
                        }*/
                    }

                    // Entry already exists, just add nextBug to it
                    else {
                        cell_bugs_Map[currentBug->getPosition()].push_back(nextBug);
                    }

                    // This will remove all other instances of the same Bug in the list
                    cell_bugs_Map[currentBug->getPosition()].unique();
                }
            }
        }
    }

    /*std::cout << "DEBUG: Printing unique bugsThatWillFight list:" << std::endl;
    for (Bug* printBug : bugsThatWillFight) {
        std::cout << printBug->asString() << std::endl;
    }*/

    // 2. Find the biggest Bug

    // Iterate every map entry (Cell : Bugs on this Cell)
    for (auto currentCell = cell_bugs_Map.begin(); currentCell != cell_bugs_Map.end(); currentCell++) {

        // currentCell->second is the std::list<Bug*> that I can iterate through now
        std::list<Bug*> bugsThatWillFight = currentCell->second;

        // Max size Bug
        Bug* imTheBiggestBug;

        // Find max size bug
        for (Bug* currentBug : bugsThatWillFight) {

            // Set new biggest bug
            if (currentBug->getSize() > imTheBiggestBug->getSize()) {
                imTheBiggestBug = currentBug;
            }
        }

        // 3. Biggest Bug eats / adds size of all other Bugs in cell, and marks them as !isAlive
        for (Bug* currentBug : bugsThatWillFight) {

            // Set new biggest bug
            // Fight list must be more than size 1
            // currentBug can't be imTheBiggestBug
            // currentBug must be alive
            if (bugsThatWillFight.size() > 1 && currentBug != imTheBiggestBug && currentBug->getIsAlive()) {

                // Eat / Gain size of the other Bug
                imTheBiggestBug->setSize(imTheBiggestBug->getSize() + currentBug->getSize());

                // Kill the Bug, set eaten by ID
                currentBug->setIsAlive(false);
                currentBug->setEatenBy(imTheBiggestBug->getId());

                // Remove currentBug from fight list
                bugsThatWillFight.pop_back();
            }

            // Reset for next Cell list
            bugsThatWillFight.clear();
        }
    }
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

        if (!currentBug->getIsAlive()) {
            temp += " Eaten by [" + std::to_string(currentBug->getEatenBy()) + "]";
        }

        bugHistoryListOut.push_back(temp);
    }

    return bugHistoryListOut;
}

void Board::writeGameHistoryToFile() {

    // Using this page: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm

    // Create time struct
    time_t timeNow = time(nullptr);

    // Get the current date and make it into a string
    char *dateTime = ctime(&timeNow);
    std::string dateTimeString = dateTime;
    dateTimeString = dateTimeString.substr(0, dateTimeString.length()-1);

    // Replace spaces with _
    std::replace(dateTimeString.begin(), dateTimeString.end(), ' ', '_');
    // Replace : with -
    std::replace(dateTimeString.begin(), dateTimeString.end(), ':', '-');

    // Create filename
    std::string fileName = "./game-history/A_Bugs_Life_" + dateTimeString + ".txt";

    std::ofstream file(fileName);

    // Get histories to write
    std::list<std::string> toWrite = this->getAllBugHistories();

    if (file.is_open()) {
        // Write them all into the file
        for (std::string currentBugHistory : toWrite) {
            std::cout << "Writing to file: " + currentBugHistory << std::endl;
            file << currentBugHistory << std::endl;
        }

        // Close file
        file.close();
    }

    else {
        std::cout << "Error: Can't write output file. Quitting..." << std::endl;
    }
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

// Named after Mode 7 on the SNES Super FX Chip, even though this is just 2D and doesn't try to simulate 3D...
void Board::sfmlMode7() {

    // Based off of the sample code "SFML Drawing App"
    // repo: https://github.com/delboy8080/SFML_Sample2

    srand(time(NULL));

    // Game setup
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML Jug's Life");
    sf::CircleShape playerBug(40);
    playerBug.setPosition(10, 10);
    playerBug.setFillColor(sf::Color::Red);
    std::vector<sf::RectangleShape> squares;

    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            sf::RectangleShape cell(sf::Vector2f(102.4,102.4));
            cell.setPosition(x*102.4, y*102.4);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);
            squares.push_back(cell);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased)
            {
                int x = playerBug.getPosition().x;
                int y = playerBug.getPosition().y;

                if (event.key.code == sf::Keyboard::Up)
                {
                    if (y > 24)
                        playerBug.setPosition(x, y - 102);

                    tap();
                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    if (y < 922)
                        playerBug.setPosition(x, y + 102);

                    tap();
                }

                if (event.key.code == sf::Keyboard::Left)
                {
                    if (x > 24)
                        playerBug.setPosition(x - 102, y);

                    tap();
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    if (x < 922)
                        playerBug.setPosition(x + 102, y);

                    tap();
                }
            }
        }

        // Refresh screen with white
        window.clear(sf::Color::White);

        for (sf::RectangleShape sh:squares)
        {
            window.draw(sh);
        }

        std::list<sf::CircleShape> gameEntitiesToDraw;
        gameEntitiesToDraw.push_back(playerBug);

        for (Bug* bugToAddToDraw : allBugs) {

            // Enemy Bug Setup
            sf::CircleShape bugEntity(40);

            // Set colour based on type
            if (bugToAddToDraw->getClass() == "Crawler" && bugToAddToDraw->getIsAlive()) {
                bugEntity.setFillColor(sf::Color::Yellow);
            } else if (bugToAddToDraw->getClass() == "Hopper" && bugToAddToDraw->getIsAlive()) {
                bugEntity.setFillColor(sf::Color::Blue);
            } else if (bugToAddToDraw->getClass() == "Indecisus" && bugToAddToDraw->getIsAlive()) {
                bugEntity.setFillColor(sf::Color::Green);
            }

            // Set position
            bugEntity.setPosition((bugToAddToDraw->getPosition().first*102.4) + 10, (bugToAddToDraw->getPosition().second*102.4) + 10);

            gameEntitiesToDraw.push_back(bugEntity);
        }

        // Drawing all entities to game
        for (sf::CircleShape gameEntity : gameEntitiesToDraw) {
            window.draw(gameEntity);
        }

        window.display();
    }
}
