// 
// 234218 Data Structures 1.
// Semester: 2025A (Winter).
// Wet Exercise #1.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef PLAINS25WINTER_WET1_H_
#define PLAINS25WINTER_WET1_H_

#include "wet1util.h"

class Plains {
private:
    //
    // Here you may add anything you want
    //
    AVLTREE<horse> horses;
    AVLTREE<herd> herds;
    AVLTREE<herd> empty_herds;

    
public:
    // <DO-NOT-MODIFY> {
    /*
    Init 3 AVL trees for horse, herd, emptyherd
     Zagoury*/
    Plains();

    //Nitay
    ~Plains();

    /*
    create empty herd and push to empty_herd AVL
     Nitay*/
    StatusType add_herd(int herdId);

    /*
    delete herd from AVL, if has horses in it return FAILURE
     Zagoury*/
    StatusType remove_herd(int herdId);

    /*
    create horse with out herd or followgroup and with speed as given and push to horse AVL
     Nitay*/
    StatusType add_horse(int horseId, int speed);

    /*
    add horse to herd with no follow group and no followers. return FAILURE if no horse or herd with given ID or
    the horse is already in other herd
     Zagoury*/
    StatusType join_herd(int horseId, int herdId);

    /*
    if horse1 is the only member of this group do horse1->group_previous->followgroup = null
    remove horse1 from follow group
    if horse2->followGroup is empty
    do horse2->followgroup = horse1
    else insert horse1 to horse2 followers linked list: go to horse2 follow group and insert horse1 at front
     Nitay*/
    StatusType follow(int horseId, int horseToFollowId);

    /*
    if horse->followgroup = null:
    remove from horse->herd linked list, return
    else merge horse->followGroup with herd->horses
     Zagoury*/
    StatusType leave_herd(int horseId);

    /*
    find horse and return his speed
     Nitay*/
    output_t<int> get_speed(int horseId);

    /*
    while (horse_t follow group is not null)
    check if horse1 is in horse2 follow group
    if yes, return true
    else check in each horse_t from horse2 follow group if horse1 is there.
     Zagoury*/
    output_t<bool> leads(int horseId, int otherHorseId);

    /*
    if herd->horses size is 1 return SUCCESS and true else FAILURE and false
     Nitay*/
    output_t<bool> can_run_together(int herdId);
    // } </DO-NOT-MODIFY>
};

#endif // PLAINS25WINTER_WET1_H_
