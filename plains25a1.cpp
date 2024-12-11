// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"

    
Plains::Plains() : horses(AVLTree<Horse>()),
                   herds(AVLTree<Herd>()),
                   empty_herds(AVLTree<Herd>()){}

Plains::~Plains()
{
    
}

StatusType Plains::add_herd(int herdId)
{
    return StatusType::FAILURE;
}

StatusType Plains::remove_herd(int herdId)
{   
    if(herdId <=0)
        return StatusType::INVALID_INPUT;
    Herd h1(herdId);
    try{
        if(empty_herds.deleteNode(h1)){
           return StatusType::SUCCESS; 
        }else{
            return StatusType::FAILURE;
        }
    }catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Plains::add_horse(int horseId, int speed)
{
    if(horseId <=0 || speed <= 0)
        return StatusType::INVALID_INPUT;
    Horse current(horseId, speed);
    try{
        if(horses.insert(current)){
           return StatusType::SUCCESS; 
        }else{
            return StatusType::FAILURE;
        }
    }catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Plains::join_herd(int horseId, int herdId)
{
    if(horseId <=0 || herdId <= 0)
        return StatusType::INVALID_INPUT;
    Horse current(horseId, 0);
    Herd h1(herdId);
    shared_ptr<AVLNode<Horse>> horse = horses.search(current);
    if (horse == nullptr || horse->value.herd != nullptr)
    {
        return StatusType::FAILURE;
    }
    shared_ptr<AVLNode<Herd>> herd = herds.search(h1);
    if (herd == nullptr)
    {
        herd = empty_herds.search(h1);
        if (herd == nullptr)
        {
            return StatusType::FAILURE;
        }else{
            try{
                herds.insert(herd->data());
                empty_herds.deleteNode(herd->data());
            }catch(...){
                return StatusType::ALLOCATION_ERROR;
            }
            herd = herds.search(h1);
        } 
    }
    try{
        horse->value.followGroup_next = 
        herd->value.leader_horses;
        herd->value.leader_horses = horse;
    }catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::follow(int horseId, int horseToFollowId)
{
    return StatusType::FAILURE;
}

StatusType Plains::leave_herd(int horseId)
{
    if(horseId <=0)
        return StatusType::INVALID_INPUT;
    Horse current(horseId, 0);
    shared_ptr<AVLNode<Horse>> horse = horses.search(current);
    if (horse == nullptr || horse->value.herd == nullptr)
    {
        return StatusType::FAILURE;
    }
    if (horse->value.first_follower == nullptr)
    {
        if (horse->value.followGroup_previous != nullptr)
        {
            if (horse->value.followGroup_previous->value.first_follower 
                = horse)
            {
                horse->value.followGroup_previous->value.first_follower = 
                horse->value.followGroup_next;
            }
            horse->value.followGroup_previous->value.followGroup_next = 
            horse->value.followGroup_next;
        }
        if (horse->value.followGroup_next != nullptr)
        {
            horse->value.followGroup_next->value.followGroup_previous = 
            horse->value.followGroup_previous;
        }
        
        
    }
    


}

output_t<int> Plains::get_speed(int horseId)
{
    return 0;
}

output_t<bool> Plains::leads(int horseId, int otherHorseId)
{
    return false;
}

output_t<bool> Plains::can_run_together(int herdId)
{
    return false;
}
