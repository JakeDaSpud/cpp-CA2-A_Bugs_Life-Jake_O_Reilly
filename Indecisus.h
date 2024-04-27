
#ifndef A_BUGS_LIFE_JAKE_O_REILLY_CA2_INDECISUS_H
#define A_BUGS_LIFE_JAKE_O_REILLY_CA2_INDECISUS_H

#include "Bug.h"

class Indecisus : public Bug {

protected:
    // How long between each 2-cell movements
    int hopInterval;
    // Actual timer to 0 of when to do 2-cell movement
    int hopCountdown;
    virtual void move();

public:
    Indecisus(int id, std::pair<int, int> position, direction direction, int size, int hopInterval): Bug(id, position, direction, size), hopInterval(hopInterval) {
        this->hopCountdown = hopInterval;
    }

    virtual std::string asString();
    virtual std::string getClass();

    int getHopInterval() const;
    void setHopInterval(int hopInterval);

    int getHopCountdown() const;
    void setHopCountdown(int hopCountdown);

    // Destructor
    ~Indecisus();
};


#endif //A_BUGS_LIFE_JAKE_O_REILLY_CA2_INDECISUS_H
