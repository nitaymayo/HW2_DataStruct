// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a1.h"

int Horse::horse_num = 0;
int Herd::herd_num = 0;

typedef shared_ptr<Horse> horse_node_ptr;
typedef shared_ptr<Herd> herd_node_ptr;

Plains::Plains() : horses(AVLTree<Horse>()),
                   herds(AVLTree<Herd>()),
                   empty_herds(AVLTree<Herd>()){}

Plains::~Plains() {
    empty_herds.clear();  // Assuming `clear` is implemented in AVLTree
    herds.clear();
    horses.clear();
};

StatusType Plains::add_herd(int herdId)
{
  if (herdId <= 0) return StatusType::INVALID_INPUT;

  Herd newHerd(herdId);
  if (herds.search(newHerd) != nullptr ||
      empty_herds.search(newHerd) != nullptr)
      return StatusType::FAILURE;

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
        if(horses.insert(current)) {
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    }catch(bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Plains::join_herd(int horseId, int herdId)
{
    if(horseId <=0 || herdId <= 0)
        return StatusType::INVALID_INPUT;
    Horse current(horseId, 0);
    shared_ptr<AVLNode<Horse>> temp_horse = horses.search(current);
    if (temp_horse == nullptr){
        return StatusType::FAILURE;
    }
    horse_node_ptr horse = temp_horse->data();
    if (horse == nullptr || horse->getHerd() != nullptr)
    {
        return StatusType::FAILURE;
    }
    Herd h1(herdId);
    shared_ptr<AVLNode<Herd>> temp_herd = herds.search(h1);
    herd_node_ptr herd = temp_herd != nullptr ? temp_herd->data() : nullptr;
    // if no herd in herds
    if (herd == nullptr)
    {
        // check if herd exists in empty_herds
        temp_herd =  empty_herds.search(h1);
        herd = temp_herd != nullptr ? temp_herd->data() : nullptr;
        // if not then Failure
        if (herd == nullptr)
        {
            return StatusType::FAILURE;
        }
        try{
            herds.insert(*herd);
            empty_herds.deleteNode(*herd);
        }catch(...){
            return StatusType::ALLOCATION_ERROR;
        }
        herd = herds.search(h1)->data();
    }
    try{
        herd->joinHerd(horse);
        horse->joinHerd(herd);
    }catch(...){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::follow(int horseId, int horseToFollowId)
{
    if (horseId <=0 || horseToFollowId <= 0 || horseId == horseToFollowId)
        return StatusType::INVALID_INPUT;
    Horse horseFollower(horseId, 0), horseToFollow(horseToFollowId, 0);
    shared_ptr<AVLNode<Horse>> temp_horse = horses.search(horseFollower);
    shared_ptr<AVLNode<Horse>> temp_other = horses.search(horseToFollow);
    if (temp_horse == nullptr || temp_other == nullptr){
        return StatusType::FAILURE;
    }
    horse_node_ptr horse = temp_horse->data();
    horse_node_ptr toFollow = temp_other->data();
    if (horse->getHerd() == nullptr || horse->getHerd() != toFollow->getHerd())
        return StatusType::FAILURE;

    horse->follow(toFollow);
    return StatusType::SUCCESS;
}

StatusType Plains::leave_herd(int horseId)
{
    if(horseId <=0)
        return StatusType::INVALID_INPUT;
    Horse current(horseId, 0);
    shared_ptr<AVLNode<Horse>> temp_horse = horses.search(current);
    if (temp_horse == nullptr){
        return StatusType::FAILURE;
    }
    horse_node_ptr horse = temp_horse->data();
    if (horse == nullptr || horse->getHerd() == nullptr)
    {
        return StatusType::FAILURE;
    }
    herd_node_ptr temp_herd = horse->getHerd();
    temp_herd->leaveHerd(horse->node.lock());
    horse->leaveHerd();
    if (temp_herd->m_horses == nullptr)
    {
        try{
            empty_herds.insert(*temp_herd);
            herds.deleteNode(*temp_herd);
        }catch(...){
            return StatusType::ALLOCATION_ERROR;
        }
    }
    return StatusType::SUCCESS;
}

output_t<int> Plains::get_speed(int horseId)
{
    if (horseId <= 0) return output_t<int>(StatusType::INVALID_INPUT);

    Horse current(horseId, 0);
    shared_ptr<AVLNode<Horse>> temp_horse = horses.search(current);
    if (temp_horse == nullptr){
        return StatusType::FAILURE;
    }
    horse_node_ptr horse = temp_horse->data();
    if (horse == nullptr) return output_t<int>(StatusType::FAILURE);

    return output_t<int>(horse->getSpeed());
}

output_t<bool> Plains::leads(int horseId, int otherHorseId)
{
    if(horseId <=0 || otherHorseId <= 0 || horseId == otherHorseId)
        return StatusType::INVALID_INPUT;
    Horse h1(horseId, 0);
    shared_ptr<AVLNode<Horse>> temp_horse = horses.search(h1);
    Horse h2(otherHorseId, 0);
    shared_ptr<AVLNode<Horse>> temp_other = horses.search(h2);
    if (temp_horse == nullptr || temp_other == nullptr)
    {
        return StatusType::FAILURE;
    }
    horse_node_ptr horse = temp_horse->data();
    horse_node_ptr other = temp_other->data();
    return has_leading_chain(horse, other);
}

bool Plains::has_leading_chain(horse_node_ptr horse, horse_node_ptr other){
    if (!other->getHerd() ||
        !horse->getHerd() ||
        other->getHerd() != horse->getHerd()){
        return false;
    }
    int count = 0;
    int n_herd = horse->getHerd()->getCount() - 1;
    while (horse->getLeader() != nullptr
        && count < n_herd)
    {
        horse = horse->getLeader();
        if (horse == other){
            return true;
        }
        count++;
    }
    return false;
 }

bool Plains::go_over_follow_chain(shared_ptr<MyNode> horse,
                          shared_ptr<MyNode> leader,
                          int chain_count){
    if (horse->getHorse()->getLeader() == nullptr) return true;
    // run on chain untiinsert(node->right, data)l you get to leader
    while (horse->getHorse()->getLeader() != leader->getHorse()){
        // if got back on current chain so a circle exist in herd and they cant run togather
        if (horse->chain_num == chain_count) return false;
        // if got to an existing chain so horse is connected to leader so return true
        if (horse->chain_num < chain_count &&
            horse->chain_num != -1) break;
        // update horse chain num and proceed to next horse
        horse->chain_num = chain_count;
        horse = horse->getHorse()->getLeader()->node.lock();
           }
    horse->chain_num = chain_count;
    leader->chain_num = chain_count;
    return true;
}

output_t<bool> Plains::can_run_together(int herdId)
{
    if (herdId <= 0)
        return output_t<bool>(StatusType::INVALID_INPUT);
        
    Herd herd_obj(herdId);
    shared_ptr<AVLNode<Herd>> temp_herd = herds.search(herd_obj);
    herd_node_ptr herd = temp_herd ? temp_herd->data() : nullptr;

    if (herd == nullptr) return output_t<bool>(StatusType::FAILURE);

    shared_ptr<MyNode> a_horse = herd->m_horses, leader = nullptr;

    if (herd->getCount() == 1) return output_t<bool>(true);

    // find leader and make sure there is exactly 1
    while (a_horse != nullptr){
      // reset chain number field
      a_horse->chain_num = -1;
      if (a_horse->getHorse()->getLeader() == nullptr){
        // if no leader yet make a_horse leader
        if (leader == nullptr) leader = a_horse;
        // else there are more then 2 leaders so herd cant run
        else return output_t<bool>(false);
      }
      a_horse = a_horse->next;
    }
    if (!leader) return output_t<bool>(false);

    // iterate over herd and assign chain number
    int chain_counter = 1;

    a_horse = herd->m_horses;
    while (a_horse != nullptr){
      if (go_over_follow_chain(a_horse, leader, chain_counter)){
          a_horse = a_horse->next;
          chain_counter++;
      } else return output_t<bool>(false);
    }

    return output_t<bool>(true);
}
