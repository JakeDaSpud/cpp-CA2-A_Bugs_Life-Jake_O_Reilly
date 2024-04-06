
#ifndef A_BUGS_LIFE_JAKE_O_REILLY_CA2_CONVERSION_UTILS_H
#define A_BUGS_LIFE_JAKE_O_REILLY_CA2_CONVERSION_UTILS_H

#include <utility>
#include <string>
#include <iostream>
#include "Crawler.h"
#include "Hopper.h"
// #include custom buggy

class conversion_utils {
public:
    static direction stodir(const std::string &stringIn);
    static std::string dirtos(const direction &dirIn);

    // Exception handling functions
    static int trystoi(const std::string &stoiString);
};


#endif //A_BUGS_LIFE_JAKE_O_REILLY_CA2_CONVERSION_UTILS_H
