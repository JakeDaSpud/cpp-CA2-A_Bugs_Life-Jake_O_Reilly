
#include "conversion_utils.h"

// try to convert a string to integer
int conversion_utils::trystoi(const std::string &stoiString) {

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

// take string and return direction
direction conversion_utils::stodir(const std::string &stringIn) {
    if (stringIn == "NORTH") {return direction::NORTH;}
    else if (stringIn == "EAST") {return direction::EAST;}
    else if (stringIn == "SOUTH") {return direction::SOUTH;}
    else {return direction::WEST;}
}

// take direction and return string
std::string conversion_utils::dirtos(const direction &dirIn) {
    if (dirIn == direction::NORTH) {return "NORTH";}
    else if (dirIn == direction::EAST) {return "EAST";}
    else if (dirIn == direction::SOUTH) {return "SOUTH";}
    else if (dirIn == direction::WEST) {return "WEST";}
    return "";
}
