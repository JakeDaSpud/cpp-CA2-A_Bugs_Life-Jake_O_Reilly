
#ifndef A_BUGS_LIFE_JAKE_O_REILLY_CA2_MAIN_H
#define A_BUGS_LIFE_JAKE_O_REILLY_CA2_MAIN_H

#include <iostream>
#include <utility>
#include <vector>
#include "Crawler.h"
#include "Hopper.h"
#include <fstream>
#include <sstream>
#include "conversion_utils.h"

// Functions for main.cpp
int main();
void printMenu();
void populateBugsFromFile(std::vector<Bug*> &bugVector, std::string fileName = "inputBugs.txt");

#endif //A_BUGS_LIFE_JAKE_O_REILLY_CA2_MAIN_H
