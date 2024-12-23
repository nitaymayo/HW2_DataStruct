//
// Created by nitaymayo on 12/8/24.
//

#ifndef HERD_H
#define HERD_H
#include "Horse.h"


class Herd {
    int ID;
    int counter;
    static int herd_num;
public:

    shared_ptr<MyNode> m_horses;
    explicit Herd(const int ID): ID(ID), counter(0) {
        herd_num++;
}
    ~Herd() {
        auto current = m_horses;
        while (current) {
            auto next = current->next;
            current->current_horse.reset();
            current.reset();
            current = next;
        }
    };

    int getID() const {
        return ID;
    }
    int getCount() const {return counter;}


    bool joinHerd(shared_ptr<Horse> &horse){
        if (!horse) {
            throw invalid_argument("Horse cannot be null");
        }
        shared_ptr<MyNode> current = make_shared<MyNode>(horse, m_horses, nullptr);
        horse->node = current;

        if (m_horses != nullptr) {
            m_horses->previous = current;
        }
        m_horses = current;

        counter++;
        return true;
    }
    void leaveHerd(shared_ptr<MyNode> node){
        // if node is first in the list
        if (node->previous.lock() == nullptr) {
            m_horses = node->next;;
        } else {
            // if node is inside the list
            auto previous = node->previous.lock();
            previous->next = node->next;
            if (node->next) {
                node->next->previous = previous;
            }
        }
        node->next.reset();
        node->current_horse.reset();
        counter--;
        /*
        if (node->next != nullptr){
            node->next->previous = node->previous;
        }
        if (previous)
            previous->next = node->next;
        else if(node == m_horses)
            m_horses = node->next;*/
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