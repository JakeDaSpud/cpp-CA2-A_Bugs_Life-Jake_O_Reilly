
#include "Indecisus.h"

void Indecisus::move() {
    std::printf("Indecisus: move() called");
}

bool Indecisus::isWayBlocked() {
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

int Indecisus::getHopInterval() const {
    return hopInterval;
}

void Indecisus::setHopInterval(int hopInterval) {
    Indecisus::hopInterval = hopInterval;
}

int Indecisus::getHopCountdown() const {
    return hopCountdown;
}

void Indecisus::setHopCountdown(int hopCountdown) {
    Indecisus::hopInterval = hopCountdown;
}

std::string Indecisus::asString() {
    std::string out = "";

    out += "Indecisus: id[" + std::to_string(this->getId()) + "] ";
    out += "position[x: " + std::to_string(this->getPosition().first) + ", y: " + std::to_string(this->getPosition().second) + "] ";
    out += "dir[" + conversion_utils::dirtos(this->facingDirection) + "] "; //using dirtos()
    out += "size[" + std::to_string(this->getSize()) + "] ";
    out += "hopInterval[" + std::to_string(this->getHopInterval()) + "] ";
    out += "hopCountdown[" + std::to_string(this->getHopCountdown()) + "]";

    return out;
}

std::string Indecisus::getClass() {
    return "Indecisus";
}

Indecisus::~Indecisus() {}
