
#include "Crawler.h"

 void Crawler::move() {
    //TODO
    // Implement move()
    // Moves by 1 in facingDirection
    // If isWayBlocked(), can't move, choose new random direction
    // Add new position to position history
    //std::printf("Crawler: move() called");

    // If way is blocked, choose random new direction
    // Seed random using unix time
    while (isWayBlocked()) {
        srand(time(nullptr));

        // Get random 1-4, change direction
        switch (1 + rand() % 4) {
            case 1: facingDirection = direction::NORTH; break;
            case 2: facingDirection = direction::EAST; break;
            case 3: facingDirection = direction::SOUTH; break;
            case 4: facingDirection = direction::WEST; break;
        }
    }

    if (facingDirection == direction::NORTH) {
        position.second--;
    } else if (facingDirection == direction::EAST) {
        position.first++;
    } else if (facingDirection == direction::SOUTH) {
        position.second++;
    } else if (facingDirection == direction::WEST) {
        position.first--;
    }

    // Add new position
    path.push_back(this->position);
}

bool Crawler::isWayBlocked() {
    if (facingDirection == direction::NORTH && position.second == 0) {
        return true;
    } else if (facingDirection == direction::EAST && position.first == 9) {
        return true;
    } else if (facingDirection == direction::SOUTH && position.second == 9) {
        return true;
    } else if (facingDirection == direction::WEST && position.first == 0) {
        return true;
    } else {
        return false;
    }
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

std::string Crawler::getClass() {
    return "Crawler";
}

Crawler::~Crawler() = default;
