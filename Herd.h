//
// Created by nitaymayo on 12/8/24.
//

#ifndef HERD_H
#define HERD_H
#include <memory>


class Herd {
    friend class Horse;
    int ID;
    std::shared_ptr<Horse> leader_horses;
public:
    Herd(int ID): ID(ID) {}
};
#endif //HERD_H