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

public:
    int timestamp = -1;
    std::shared_ptr<AVLNode<Horse>> herd_next;
    std::shared_ptr<AVLNode<Horse>> herd_previous;
    std::shared_ptr<AVLNode<Horse>> leader;
    std::shared_ptr<AVLNode<Herd>> herd;
    Horse(const int ID, const int speed): ID(ID), speed(speed) {};

    ~Horse() = default;

    int getID() const {
        return ID;
    }
    int getSpeed() const {
        return speed;
    }
};

inline bool operator==(const Horse &h1, const Horse &h2) {
    return h1.getID() == h2.getID();
}
inline bool operator<(const Horse &h1, const Horse &h2) {
    return h1.getID() < h2.getID();
}
inline bool operator>(const Horse &h1, const Horse &h2) {
    return h1.getID() > h2.getID();
}



#endif //HORSE_H
