
#include "Hopper.h"

void Hopper::move() {
    //TODO
    // Move by hopLength in facingDirection
    // If isWayBlocked true, can't move
    // If can't move full hopLength, moves to edge of board, then choose random direction
    // Add new position to position history
    //std::printf("Hopper: move() called");

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
        position.second = position.second - hopLength;
    } else if (facingDirection == direction::EAST) {
        position.first = position.first + hopLength;
    } else if (facingDirection == direction::SOUTH) {
        position.second = position.second + hopLength;
    } else if (facingDirection == direction::WEST) {
        position.first = position.first - hopLength;
    }

    // Too far North
    if (position.second < 0) {
        position.second = 0;
    }

    // Too far East
    if (position.first > 9) {
        position.first = 9;
    }

    // Too far South
    if (position.second > 9) {
        position.second = 9;
    }

    // Too far West
    if (position.first < 0) {
        position.first = 0;
    }

    // Add new position
    path.push_back(this->position);
}

bool Hopper::isWayBlocked() {
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

int Hopper::getHopLength() const {
    return hopLength;
}

void Hopper::setHopLength(int hopLength) {
    Hopper::hopLength = hopLength;
}

std::string Hopper::asString() {
    std::string out = "";

    //int id, std::pair<int, int> position, direction direction, int size, int hopLength
    //out += "Hopper: id[] position[x: , y:] dir[] size[]";
    out += "Hopper: id[" + std::to_string(this->getId()) + "] ";
    out += "position[x: " + std::to_string(this->getPosition().first) + ", y: " + std::to_string(this->getPosition().second) + "] ";
    out += "dir[" + conversion_utils::dirtos(this->facingDirection) + "] "; //using dirtos()
    out += "size[" + std::to_string(this->getSize()) + "] ";
    out += "hopLength[" + std::to_string(this->getHopLength()) + "]";

    return out;
}

std::string Hopper::getClass() {
    return "Hopper";
}

Hopper::~Hopper() {

}
