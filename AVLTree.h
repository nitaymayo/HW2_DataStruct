//
// Created by nitaymayo on 12/7/24.
//

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <memory>


using namespace std;

template<class T>
class AVLNode {
public:
  T value;
  shared_ptr<AVLNode<T>> left;
  shared_ptr<AVLNode<T>> right;
  int height;

  explicit AVLNode(T k):value(k),left(),right(),height(1){}

  ~AVLNode() {};

  T &data() {
    return value;
  }
  void setData(T data) {
    this->value = data;
  }
  int getHeight() {
    return height;
  }
};

template<class T>
class AVLTree {
private:
  shared_ptr<AVLNode<T>> root;

  //Zagoury
  shared_ptr<AVLNode<T>> rotateLeft(shared_ptr<AVLNode<T>> node);

  //Nitay V
  shared_ptr<AVLNode<T>> rotateRight(shared_ptr<AVLNode<T>> node);

  //Zagoury
  int height(shared_ptr<AVLNode<T>> node);

  //Nitay V
  int balanceFactor(shared_ptr<AVLNode<T>> node);

  //Zagoury
  shared_ptr<AVLNode<T>> minValueNode(shared_ptr<AVLNode<T>> node);

  //Nitay V
  shared_ptr<AVLNode<T>> insert(shared_ptr<AVLNode<T>> node, T &data);

  //Nitay V
  shared_ptr<AVLNode<T>> deleteNode(shared_ptr<AVLNode<T>> node, T &data);

  shared_ptr<AVLNode<T>> search(shared_ptr<AVLNode<T>> node, T &data);

  void clear(shared_ptr<AVLNode<T>> &node) {
    if (node) {
      auto left = node->left, right = node->right;
      node.reset();
      clear(left);
      clear(right);
    }
  }

  void printInorder(shared_ptr<AVLNode<T>> root)
  {
    if (!root) {
      return;
    }
    if (root->left) printInorder(root->left);
    cout << root->data() << " ";
    if (root->right) printInorder(root->right);
  }

  void printPreorder(shared_ptr<AVLNode<T>> root)
  {
    if (root != nullptr) {
      cout << root->data() << " ";
      printPreorder(root->left);
      printPreorder(root->right);
    }
  }

  shared_ptr<AVLNode<T>> fixWithRotations(shared_ptr<AVLNode<T>> node);

public:
  AVLTree():root(){};

  ~AVLTree() {
    if (root) {
      auto left = root->left, right = root->right;
      root.reset();
      clear(left);
      clear(right);
    }
  };

  void clear() {
    if (root) {
      auto left = root->left, right = root->right;
      root.reset();
      clear(left);
      clear(right);
    }
  }


  //Nitay V
  bool insert(T &data);

  //Zagoury
  shared_ptr<AVLNode<T>> search(T &data);

  //Nitay V
  bool deleteNode(T &data);

  void printInorder(){
    if (root != nullptr) {
      printInorder(root->left);
      cout << root->data() << " ";
      printInorder(root->right);
    }
    cout << endl;
  }
  void printPreorder(){
    if (root != nullptr) {
      cout << root->data() << " ";
      printPreorder(root->left);
      printPreorder(root->right);
    }
    cout << endl;
  }

  void printBalanceFactorsInorder(){printBalanceFactorsInorder(this->root); cout<<endl;}
  void printBalanceFactorsInorder(shared_ptr<AVLNode<T>> node){
    if (node != nullptr) {
      printBalanceFactorsInorder(node->left);
      cout << this->balanceFactor(node) << " ";
      printBalanceFactorsInorder(node->right);
    }

  }
};

template<class T>
int AVLTree<T>::balanceFactor(shared_ptr<AVLNode<T>> node)
{
  if (node == nullptr)
    return 0;
  return height(node->left) - height(node->right);
}


template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::minValueNode(shared_ptr<AVLNode<T>> node) {
  // if there isnt smaller node return this node
  if (node->left == nullptr) return node;
  // else go down and left in the tree
  return minValueNode(node->left);
}

template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::search(T &data) {
  if (this->root == nullptr) return nullptr;

  try {
    if (this->root->data() == data) return this->root;

    if (this->root->data() > data) return this->root->left ? search(this->root->left, data) : nullptr;

    return this->root->right ? search(this->root->right, data) : nullptr;
  } catch (logic_error &e) {
    return nullptr;
  }
}

template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::search(shared_ptr<AVLNode<T>> node, T &data) {
  if (node == nullptr) throw logic_error("Data not found");

  if (node->data() == data) return node;

  if (node->data() > data) return search(node->left, data);

  return search(node->right, data);
}

template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::fixWithRotations(shared_ptr<AVLNode<T>> node) {

  // calculate balance factor
  int nodeBalanceFactor = balanceFactor(node);

  //  RR
  if (nodeBalanceFactor == -2 && balanceFactor(node->right) <= 0){
    return rotateLeft(node);
  }
  // LL
  if (nodeBalanceFactor == 2 && balanceFactor(node->left) >= 0){
    return rotateRight(node);
  }
  // RL
  if (nodeBalanceFactor == -2 && balanceFactor(node->right) == 1){
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  // LR
  if (nodeBalanceFactor == 2 && balanceFactor(node->left) == -1){
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  return node;
}

template<class T>
bool AVLTree<T>::insert(T &data){
  if (this->root == nullptr){
    this->root = make_shared<AVLNode<T>>(data);
    return true;
  }
  try {
    if (this->root->data() > data){
      if (this->root->left == nullptr) this->root->left = make_shared<AVLNode<T>>(data);
      else  this->root->left = insert(this->root->left, data);

    } else if (this->root->data() < data){
      if (this->root->right == nullptr) this->root->right = make_shared<AVLNode<T>>(data);
      else this->root->right = insert(this->root->right, data);
    } else {
      return false;
    }
  } catch (logic_error &e) {
    return false;
  }
  this->root->height = 1 + max(height(root->left), height(root->right));
  root = fixWithRotations(root);
  return true;
}

template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::insert(shared_ptr<AVLNode<T>> node, T &data){
  if (node == nullptr){
    return make_shared<AVLNode<T>>(data);
  }

  if (node->data() == data) {
    node.reset();
    throw logic_error("data already exists");
  }

  // recursive insertion of the new node
  if (data < node->data())
    node->left = insert(node->left, data);
  else if (data > node->data())
    node->right = insert(node->right, data);
  else
    return node;

  //update balance factor of this node
  node->height = 1 + max(height(node->left), height(node->right));

  // fix the node with rotations and return new root
  return fixWithRotations(node);
}

template<class T>
bool AVLTree<T>::deleteNode(T &data) {
  try {

    if (this->root == nullptr) throw logic_error("Data not found");

    if (this->root->data() == data) {
      this->root = deleteNode(this->root, data);
    } else if (this->root->data() > data) {
      this->root->left = deleteNode(this->root->left, data);
    } else {
      this->root->right = deleteNode(this->root->right, data);
    }
    return true;
  } catch (logic_error &e) {
    return false;
  }
}

template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::deleteNode(shared_ptr<AVLNode<T>> node, T &data) {

  // in case the node to delete doesnt exist in the tree return false
  if (node == nullptr) throw logic_error("Data not found");


  if (node->data() > data) {
    node->left = deleteNode(node->left, data);
  } else if (node->data() < data) {
    node->right = deleteNode(node->right, data);
  } else if (node->data() == data) {
    // this node should be deleted
    // case if node has no son
    if (node->left == nullptr && node->right == nullptr) {
      node.reset();
      return nullptr;
    } else if (node->right == nullptr) {
      // node has only left son
      auto leftSon = node->left;
      node.reset();
      return leftSon;
    } else if (node->left == nullptr) {
      // node has only right son
      auto rightSon = node->right;
      node.reset();
      return rightSon;
    } else {
      // Node has 2 children
      // switch between the smallest right son and node
      shared_ptr<AVLNode<T>> smallest_right_successor = minValueNode(node->right);
      node->setData(smallest_right_successor->data());
      // delete the smallest son (he is transferred to node location)
      node->right = deleteNode(node->right, smallest_right_successor->data());
    }

    if (node == nullptr) return nullptr;

    // Get balance factor
    node->height = 1 + max(height(node->left), height(node->right));

  }
  // fix with rotations and return new root
  return fixWithRotations(node);
}

template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::rotateLeft(shared_ptr<AVLNode<T>> node) {
  // save temp nodes
  shared_ptr<AVLNode<T>> RL_sub_tree = node->right->left;
  shared_ptr<AVLNode<T>> R_node = node->right;

  // rotate
  R_node->left = node;
  node->right = RL_sub_tree;

  // update height
  node->height = 1 + max(height(node->left), height(node->right));
  R_node->height = 1 + max(height(node->left), height(node->right));

  //return new subtree root
  return R_node;
}

template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::rotateRight(shared_ptr<AVLNode<T>> node) {
  // save relevant nodes
  shared_ptr<AVLNode<T>> LR_sub_tree = node->left->right;
  shared_ptr<AVLNode<T>> L_node = node->left;

  // rotate
  L_node->right = node;
  node->left = LR_sub_tree;

  //update heights
  node->height = 1 + max(height(node->left), height(node->right));
  L_node->height = 1 + max(height(node->left), height(node->right));

  // return new root
  return L_node;
}

template<class T>
int AVLTree<T>::height(shared_ptr<AVLNode<T>> node) {
  return node ? node->getHeight() : 0;
}




#endif //AVLTREE_H
