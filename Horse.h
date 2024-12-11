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
    std::shared_ptr<AVLNode<Horse>> followGroup_next;
    std::shared_ptr<AVLNode<Horse>> followGroup_previous;
    std::shared_ptr<AVLNode<Horse>> first_follower;
    // std::shared_ptr<AVLNode<Horse>> last_follower;
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
