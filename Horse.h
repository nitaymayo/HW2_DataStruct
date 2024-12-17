//
// Created by nitaymayo on 12/8/24.
//

#ifndef HORSE_H
#define HORSE_H
#include <memory>
// #include "Herd.h"


struct MyNode;
class Herd;

class Horse {
private:
    int ID;
    int speed;
    int join_timestamp;
    int following_timestamp;
    std::shared_ptr<AVLNode<Herd>> herd;
    std::shared_ptr<AVLNode<Horse>> leader;
public:

    shared_ptr<MyNode> node;

    Horse(const int ID, const int speed): ID(ID), speed(speed), join_timestamp(0), following_timestamp(-1) {};

    ~Horse() = default;

    int getID() const {
        return ID;
    }
    int getSpeed() const {
        return speed;
    }

    int getTimestamp() const {
        return join_timestamp;
    }
    std::shared_ptr<AVLNode<Herd>> getHerd(){
        return herd;
    }

    std::shared_ptr<AVLNode<Horse>> getLeader() {
        if (leader != nullptr && following_timestamp == leader->value.getTimestamp() ) {
            return leader;
        }
        return nullptr;
    }

    void follow(std::shared_ptr<AVLNode<Horse>> leader) {
        if (leader == nullptr) throw std::invalid_argument("Horse can't be null");
        following_timestamp = leader->value.getTimestamp();
        this->leader = leader;
    }

    void joinHerd(std::shared_ptr<AVLNode<Herd>> herd) {
        this->join_timestamp++;
        this->herd = herd;
    }

    void leaveHerd(){
        this->node = nullptr;
        this->herd = nullptr;
        this->leader = nullptr;
        this->join_timestamp++;
        this->following_timestamp = -1;
    }
};

inline bool operator==(const Horse &h1, const Horse &h2) {
    return h1.getID() == h2.getID();
}
inline bool operator!=(const Horse &h1, const Horse &h2) {
    return !(h1 == h2);
}
inline bool operator<(const Horse &h1, const Horse &h2) {
    return h1.getID() < h2.getID();
}
inline bool operator>(const Horse &h1, const Horse &h2) {
    return h1.getID() > h2.getID();
}

inline ostream &operator<<(ostream &os, const Horse &h) {
    os << h.getID();
    return os;
}

struct MyNode{
    shared_ptr<AVLNode<Horse>> current_horse;
    shared_ptr<MyNode> next;
    shared_ptr<MyNode> previous;
    int chain_num = -1;
};

#endif //HORSE_H
