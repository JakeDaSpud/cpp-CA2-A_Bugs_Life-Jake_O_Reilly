
#ifndef A_BUGS_LIFE_JAKE_O_REILLY_CA2_HOPPER_H
#define A_BUGS_LIFE_JAKE_O_REILLY_CA2_HOPPER_H

#include "Bug.h"
#include <list>
#include <utility>

// Public inheritance keeps protected fields protected
class Hopper: public Bug {

private:
    int hopLength;

protected:
    virtual void move() override;

public:
    // Constructor
    Hopper(int id, std::pair<int, int> position, direction direction, int size, int hopLength) {
        this->id = id;
        this->position = position;
        Bug::setFacingDirection(direction);
        this->size = size;
        this->hopLength = hopLength;

        this->isAlive = true;
        this->path = {this->position}; // Sets first move in history to be spawn position
        // example spawn code: H;102;9;0;NORTH;8;2
    };

    virtual std::string asString() override;

    int getHopLength() const;
    void setHopLength(int hopLength);

    //Destructor
    ~Hopper() override;
};

#endif //A_BUGS_LIFE_JAKE_O_REILLY_CA2_HOPPER_H
