//
// Created by nitaymayo on 12/8/24.
//

#ifndef HORSE_H
#define HORSE_H
#include <memory>
#include <utility>

struct MyNode;
class Herd;

class Horse {
private:
    int ID;
    int speed;
    int join_timestamp;
    int following_timestamp;
    std::shared_ptr<Herd> herd;
    std::weak_ptr<Horse> leader;
    static int horse_num;
public:

    weak_ptr<MyNode> node;

    Horse(const int ID, const int speed): ID(ID), speed(speed), join_timestamp(0), following_timestamp(-1) {
    };

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
    std::shared_ptr<Herd> getHerd(){
        return herd;
    }

    std::shared_ptr<Horse> getLeader() {
        shared_ptr<Horse> temp_leader = leader.lock(); 
        if (temp_leader == nullptr) return nullptr;
        if (following_timestamp == temp_leader->getTimestamp() ) {
            return temp_leader;
        }
        return nullptr;
    }

    void follow(std::shared_ptr<Horse> leader) {
        if (leader == nullptr) throw std::invalid_argument("Horse can't be null");
        following_timestamp = leader->getTimestamp();
        this->leader = leader;
    }

    void joinHerd(const std::shared_ptr<Herd> &herd) {
        this->join_timestamp++;
        this->herd = herd;
    }

    void leaveHerd(){
        this->node.reset();
        this->herd.reset();
        this->leader.reset();
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
    weak_ptr<Horse> current_horse;
    int horse_ID;
    shared_ptr<MyNode> next;
    weak_ptr<MyNode> previous;
    int chain_num = -1;

    MyNode(const shared_ptr<Horse> &horse,
            const shared_ptr<MyNode> &next,
            const shared_ptr<MyNode> &previous):current_horse(horse),
                                        horse_ID(horse->getID()),
                                        next(next),
                                        previous(previous){}

    shared_ptr<Horse> getHorse() const {
        return current_horse.lock();
    }
};

#endif //HORSE_H
