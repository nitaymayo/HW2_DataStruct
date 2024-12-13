// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"

typedef shared_ptr<AVLNode<Horse>> horse_node_ptr;
typedef shared_ptr<AVLNode<Herd>> herd_node_ptr;
    
Plains::Plains() : horses(AVLTree<Horse>()),
                   herds(AVLTree<Herd>()),
                   empty_herds(AVLTree<Herd>()){}

Plains::~Plains()
{
    
}

StatusType Plains::add_herd(int herdId)
{
  if (herdId <= 0) return StatusType::INVALID_INPUT;

  Herd newHerd(herdId);
  if (herds.search(newHerd) == nullptr) return StatusType::FAILURE;

  try{
      if (empty_herds.insert(newHerd)) return StatusType::SUCCESS;
  } catch(bad_alloc &e){
    return StatusType::ALLOCATION_ERROR;
  }
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
        horse->value.herd_next = herd->value.m_horses;
        if(herd->value.m_horses != nullptr){
            herd->value.m_horses->value.herd_previous = horse;
        }
        herd->value.m_horses = horse;
        horse->value.herd_previous = nullptr;
        horse->value.timestamp = herd->value.counter;
        herd->value.counter++;
        horse->value.herd = herd;
    }catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::follow(int horseId, int horseToFollowId)
{
  if (horseId <=0 || horseToFollowId <= 0 || horseId == horseToFollowId) return StatusType::INVALID_INPUT;

  horse_node_ptr follower = horses.search(Horse(horseId, 0)),
                 toFollow = horses.search(Horse(horseToFollowId, 0));

  if (follower == nullptr || toFollow == nullptr || follower->value.herd != toFollow->value.herd)
    return StatusType::FAILURE;

  follower->value.follow(toFollow);
  return StatusType::SUCCESS;
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
    shared_ptr<AVLNode<Herd>> temp_herd = horse->value.herd;
    if (temp_herd->value.m_horses == horse)
    {
        temp_herd->value.m_horses 
        = temp_herd->value.m_horses->value.herd_next;
    }
    if (horse->value.herd_previous!= nullptr)
    {
        horse->value.herd_previous->value.herd_next
         = horse->value.herd_next; 
    }
    if (horse->value.herd_next != nullptr)
    {
        horse->value.herd_next->value.herd_previous
         = horse->value.herd_previous; 
    }
    horse->value.herd = nullptr;
    horse->value.leader = nullptr;
    if (temp_herd->value.m_horses == nullptr)
    {
        try{
            herds.deleteNode(temp_herd->data());
            empty_herds.insert(temp_herd->data());
        }catch(...){
            return StatusType::ALLOCATION_ERROR;
        }
    }
    return StatusType::SUCCESS;
}

output_t<int> Plains::get_speed(int horseId)
{
    if (horseId <= 0) return output_t<int>(StatusType::INVALID_INPUT);

    horse_node_ptr horse = horses.search(Horse(horseId, 0));
    if (horse == nullptr) return output_t<int>(StatusType::FAILURE);

    return output_t<int>(horse->value.getSpeed());
}

output_t<bool> Plains::leads(int horseId, int otherHorseId)
{
    if(horseId <=0 || otherHorseId <= 0 || horseId == otherHorseId)
        return StatusType::INVALID_INPUT;
    Horse h1(horseId, 0);
    shared_ptr<AVLNode<Horse>> horse = horses.search(h1);
    Horse h2(otherHorseId, 0);
    shared_ptr<AVLNode<Horse>> other = horses.search(h2);
    if (horse == nullptr || other == nullptr)
    {
        return StatusType::FAILURE;
    }
    if (other->value.herd != horse->value.herd){
        return false;
    }
    while (horse->value.leader != nullptr)
    {
        if (horse->value.leader == other){
            return true;
        }
        horse = horse->value.leader;
    }
    return false;
}

output_t<bool> Plains::can_run_together(int herdId)
{
    return false;
}
