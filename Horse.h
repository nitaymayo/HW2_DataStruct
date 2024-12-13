//
// Created by nitaymayo on 12/8/24.
//

#ifndef HORSE_H
#define HORSE_H
#include <memory>
#include "Herd.h"
#include <chrono>

class Horse {
private:
    int ID;
    int speed;
    std::time_t join_timestamp;
    std::time_t following_timestamp;

public:

    std::shared_ptr<AVLNode<Horse>> herd_next;
    std::shared_ptr<AVLNode<Horse>> herd_previous;
    std::shared_ptr<AVLNode<Horse>> leader;
    std::shared_ptr<AVLNode<Herd>> herd;
    Horse(const int ID, const int speed): ID(ID), speed(speed), join_timestamp(-1), following_timestamp(-1) {};

    ~Horse() = default;

    int getID() const {
        return ID;
    }
    int getSpeed() const {
        return speed;
    }

    void follow(const std::shared_ptr<AVLNode<Horse>>& leader) {
        if (leader == nullptr) throw std::invalid_argument("Horse can't be null");
        time(&following_timestamp);
        this->leader = leader;
    }

    bool joinHerd(const std::shared_ptr<AVLNode<Herd>> &herd) {
        if (this->herd->value == herd->value) return false;
        time(&join_timestamp);
        this->herd = herd;
        return true;
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
