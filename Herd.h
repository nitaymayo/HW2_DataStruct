//
// Created by nitaymayo on 12/8/24.
//

#ifndef HERD_H
#define HERD_H
#include <memory>


struct MyNode{
    shared_ptr<AVLNode<Horse>> current_horse;
    shared_ptr<MyNode> next;
    shared_ptr<MyNode> previous;
};

class Herd {
    friend class Horse;
    int ID;
    int counter;
public:
    shared_ptr<MyNode> m_horses;
    explicit Herd(const int ID): ID(ID), counter(0) {}

    int getID() const {
        return ID;
    }
    int getCount() const {return counter;}


    bool joinHerd(shared_ptr<AVLNode<Horse>> horse){
        shared_ptr<MyNode> current = make_shared<MyNode>();
        current->current_horse = horse;
        horse->value.node = current;
        current->next = m_horses;
        current->previous = nullptr;
        m_horses->previous = current;
        m_horses = current;
        counter++;
        return true;
    }
    void leaveHerd(shared_ptr<MyNode> node){
        if (node->next != nullptr)
        {
            node->next->previous = node->previous;
        }
        if (node->previous != nullptr)
        {
            node->previous->next = node->next;
        }else if(node == m_horses){
            m_horses = node->next;
        }
        counter--;
    }
};

inline bool operator==(const Herd& lhs, const Herd& rhs) {
    return lhs.getID() == rhs.getID();
}
inline bool operator<(const Herd& lhs, const Herd& rhs) {
    return lhs.getID() < rhs.getID();
}
inline bool operator>(const Herd& lhs, const Herd& rhs) {
    return lhs.getID() > rhs.getID();
}

#endif //HERD_H