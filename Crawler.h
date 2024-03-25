
#ifndef A_BUGS_LIFE_JAKE_O_REILLY_CA2_CRAWLER_H
#define A_BUGS_LIFE_JAKE_O_REILLY_CA2_CRAWLER_H

#include "Bug.h"
#include <list>
#include <utility>

// Public inheritance keeps protected fields protected
class Crawler: public Bug {

protected:
    void move() override;

public:
    // Constructor
    Crawler(int id, std::pair<int, int> position, direction direction, int size) {
        this->id = id;
        this->position = position;
        Bug::setFacingDirection(direction);
        this->size = size;

        this->isAlive = true;
        this->path = {this->position}; // Sets first move in history to be spawn position
        // example spawn code: C;101;0;0;WEST;10
    };

};

#endif //A_BUGS_LIFE_JAKE_O_REILLY_CA2_CRAWLER_H
