//
// Created by nitaymayo on 12/8/24.
//

#ifndef HORSE_H
#define HORSE_H
#include <memory>
#include "Herd.h"

class Horse {
private:
    int ID;
    int speed;
    std::shared_ptr<Horse> followGroup_next;
    std::shared_ptr<Horse> followGroup_previous;
    std::shared_ptr<Horse> first_follower;
    std::shared_ptr<Herd> herd;

public:
    Horse(int ID, int speed): ID(ID), speed(speed) {};

    ~Horse() = default;

    int getID() const {
        return ID;
    }
    int getSpeed() const {
        return speed;
    }
};



#endif //HORSE_H
