
#ifndef A_BUGS_LIFE_JAKE_O_REILLY_CA2_HOPPER_H
#define A_BUGS_LIFE_JAKE_O_REILLY_CA2_HOPPER_H

#include "Bug.h"
#include <list>
#include <utility>

// Public inheritance keeps protected fields protected
class Hopper: public Bug {

protected:
    int hopLength;
    virtual void move();

public:
    // Constructor: Hopper() initialises a Hopper obj with full @params
    Hopper(int id, std::pair<int, int> position, direction direction, int size, int hopLength): Bug(id, position, direction, size), hopLength(hopLength) {
    // This part of the constructor is like super() for Bug's @params, then using the new hopLength to make it Hopper
        /*this->id = id;
        this->position = position;
        Bug::setFacingDirection(direction);
        this->size = size;*/
        this->hopLength = hopLength;

        /*this->isAlive = true;
        this->path = {this->position};*/ // Sets first move in history to be spawn position
        // example spawn code: H;102;9;0;NORTH;8;2
    };

    virtual std::string asString();
    virtual std::string getClass();

    int getHopLength() const;
    void setHopLength(int hopLength);

    //Destructor
    ~Hopper();
};

#endif //A_BUGS_LIFE_JAKE_O_REILLY_CA2_HOPPER_H
