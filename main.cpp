#include <iostream>
#include <utility>
#include <vector>
#include "Crawler.h"
#include "Hopper.h"

int main() {
    std::cout << "Hello, World! START..." << std::endl;

    Crawler c1 = Crawler(1, std::pair(0, 0), direction::NORTH, 1);
    Hopper h1 = Hopper(2, std::pair(1, 1), direction::SOUTH, 2, 1);

    Crawler *c1Ptr = &c1;
    Hopper *h1Ptr = &h1;

    std::vector<Bug*> bugVector = {c1Ptr, h1Ptr};

    for (auto it = bugVector.begin(); it != bugVector.end(); it++) {
        auto& item = *it;
        std::cout << item << std::endl;
    }

    return 0;
}
