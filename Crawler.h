
#ifndef A_BUGS_LIFE_JAKE_O_REILLY_CA2_CRAWLER_H
#define A_BUGS_LIFE_JAKE_O_REILLY_CA2_CRAWLER_H

#include "Bug.h"

// Public inheritance keeps protected fields protected
class Crawler : public Bug {

protected:
    virtual void move();
    virtual bool isWayBlocked();

public:
    // Constructor
    Crawler(int id, std::pair<int, int> position, direction direction, int size): Bug(id, position, direction, size) {

        this->isAlive = true;
        this->path = {this->position}; // Sets first move in history to be spawn position
        // example spawn code: C;101;0;0;WEST;10
    };

    virtual std::string asString();
    virtual std::string getClass();

    //Destructor
    ~Crawler();

};

#endif //A_BUGS_LIFE_JAKE_O_REILLY_CA2_CRAWLER_H
