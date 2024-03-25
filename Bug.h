
#ifndef A_BUGS_LIFE_JAKE_O_REILLY_CA2_BUG_H
#define A_BUGS_LIFE_JAKE_O_REILLY_CA2_BUG_H

#include <list>
#include <utility>
#include "Direction.cpp"

class Bug {
protected:
    int id;
    std::pair<int, int> position; // X, Y
    direction facingDirection; // Facing direction
    bool isAlive;
    int size; // Initially 1-20: if two Bugs fight, one with bigger size wins, and other dies, that dead Bug's size gets added to the winner's
    std::list<std::pair<int, int>> path; // List of position history

    virtual void move() = 0; // Pure virtual function with "= 0", this means Bug class cannot be instantiated
    bool isWayBlocked() { return false; };

public:
    int getId() const;
    void setId(int id);
    const std::pair<int, int> &getPosition() const;
    void setPosition(const std::pair<int, int> &position);
    direction getFacingDirection() const;
    void setFacingDirection(direction facingDirection); // Used by move(), true if facing direction is an edge of the board.
    bool getIsAlive() const;
    void setIsAlive(bool isAlive);
    int getSize() const;
    void setSize(int size);
    const std::list<std::pair<int, int>> &getPath() const;
    void setPath(const std::list<std::pair<int, int>> &path);


};

#endif //A_BUGS_LIFE_JAKE_O_REILLY_CA2_BUG_H
