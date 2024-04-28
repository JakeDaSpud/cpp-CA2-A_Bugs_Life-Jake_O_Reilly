
#include "Bug.h"

bool isWayBlocked(){
    // I don't have this implemented yet
    return false;
} // Used by move(), true if facing direction is an edge of the board.

int Bug::getId() const {
    return id;
}
void Bug::setId(int id) {
    Bug::id = id;
}
const std::pair<int, int> &Bug::getPosition() const {
    return position;
}
void Bug::setPosition(const std::pair<int, int> &position) {
    Bug::position = position;
}
direction Bug::getFacingDirection() const {
    return facingDirection;
}
void Bug::setFacingDirection(direction facingDirection) {
    Bug::facingDirection = facingDirection;
}
bool Bug::getIsAlive() const {
    return isAlive;
}
void Bug::setIsAlive(bool isAlive) {
    Bug::isAlive = isAlive;
}
int Bug::getSize() const {
    return size;
}
void Bug::setSize(int size) {
    Bug::size = size;
}
const std::list<std::pair<int, int>> &Bug::getPath() const {
    return path;
}
void Bug::setPath(const std::list<std::pair<int, int>> &path) {
    Bug::path = path;
}

int Bug::getEatenBy() const {
    return eatenBy;
}

void Bug::setEatenBy(int eatenBy) {
    Bug::eatenBy = eatenBy;
}
