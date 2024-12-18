//
// Created by nitaymayo on 12/8/24.
//

#ifndef HERD_H
#define HERD_H
#include "Horse.h"


class Herd {
    int ID;
    int counter;

public:

    shared_ptr<MyNode> m_horses;
    explicit Herd(const int ID): ID(ID), counter(0) {}

    ~Herd() = default;

    int getID() const {
        return ID;
    }
    int getCount() const {return counter;}


    bool joinHerd(shared_ptr<AVLNode<Horse>> horse){
        shared_ptr<MyNode> current = make_shared<MyNode>();
        current->current_horse = horse;
        horse->value.node = current;
        current->next = m_horses;
        current->previous.reset();
        if (m_horses != nullptr) {
            m_horses->previous = current;
        }
        m_horses = current;
        counter++;
        return true;
    }
    void leaveHerd(shared_ptr<MyNode> node){
        if (node->next != nullptr){
            node->next->pr #include "Herd.h"
evious = node->previous;
        }
        auto previous = node->previous.lock();
        if (previous)
            previous->next = node->next;
        else if(node == m_horses)
            m_horses = node->next;

        counter--;
    }
};

inline bool operator==(const Herd& lhs, const Herd& rhs) {
    return lhs.getID() == rhs.getID();
}
inline bool operator!=(const Herd& lhs, const Herd& rhs) {
    return !(lhs.getID() == rhs.getID());
}
inline bool operator<(const Herd& lhs, const Herd& rhs) {
    return lhs.getID() < rhs.getID();
}
inline bool operator>(const Herd& lhs, const Herd& rhs) {
    return lhs.getID() > rhs.getID();
}

#endif //HERD_H