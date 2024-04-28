
#include "Indecisus.h"

void Indecisus::move() {
    std::printf("Indecisus: move() called");

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

    // Move 1 place by default
    int moveDistance = 1;

    // Move 2 places
    if (hopCountdown == 0) {
        moveDistance = 2;
        hopCountdown = hopInterval;
    }

    // Move the right length this turn
    if (facingDirection == direction::NORTH) {
        position.second = position.second - moveDistance;
    } else if (facingDirection == direction::EAST) {
        position.first = position.first + moveDistance;
    } else if (facingDirection == direction::SOUTH) {
        position.second = position.second + moveDistance;
    } else if (facingDirection == direction::WEST) {
        position.first = position.first - moveDistance;
    }

    // Tick the interval counter
    hopCountdown--;

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
