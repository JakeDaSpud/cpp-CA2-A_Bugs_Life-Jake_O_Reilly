
#include "Hopper.h"

void Hopper::move() {
    //TODO
    // Move by hopLength in facingDirection
    // If isWayBlocked true, can't move
    // If can't move full hopLength, moves to edge of board, then choose random direction
    // Add new position to position history
    std::printf("Hopper: move() called");
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
