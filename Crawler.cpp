
#include "Crawler.h"

void Crawler::move() {
    //TODO
    // Implement move()
    // Moves by 1 in facingDirection
    // If isWayBlocked(), can't move, choose new random direction
    // Add new position to position history
}

std::string Crawler::asString() {
    std::string out = "";

    //int id, std::pair<int, int> position, direction direction, int size
    //out += "Crawler: id[] position[x: , y:] dir[] size[]";
    out += "Crawler: id[" + std::to_string(this->getId()) + "] ";
    out += "position[x: " + std::to_string(this->getPosition().first) + ", y: " + std::to_string(this->getPosition().second) + "] ";
    out += "dir[" + conversion_utils::dirtos(this->facingDirection) + "] "; //using dirtos()
    out += "size[" + std::to_string(this->getSize()) + "]";

    return out;
}

Crawler::~Crawler() = default;
