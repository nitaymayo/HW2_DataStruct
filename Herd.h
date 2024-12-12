//
// Created by nitaymayo on 12/8/24.
//

#ifndef HERD_H
#define HERD_H
#include <memory>


class Herd {
    friend class Horse;
    int ID;
public:
    int counter = 0;
    std::shared_ptr<AVLNode<Horse>> m_horses;
    explicit Herd(const int ID): ID(ID) {}

    int getID() const {
        return ID;
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