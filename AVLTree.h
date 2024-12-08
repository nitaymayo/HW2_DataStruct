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
  shared_ptr<AVLNode<T>> left_child;
  shared_ptr<AVLNode<T>> right_child;
  int height;

  explicit AVLNode(T k):value(k),left_child(nullptr),right_child(nullptr),height(1){}

  virtual ~AVLNode() {
    delete left_child.get();
    delete right_child.get();
  }

  T data() {
    return value;
  }

};

template<class T>
class AVLTree {
private:
  shared_ptr<AVLNode<T>> root;

  //Zagoury
  shared_ptr<AVLNode<T>> rotateLeft(AVLNode<T> *node);

  //Nitay V
  shared_ptr<AVLNode<T>> rotateRight(AVLNode<T> *node);

  //Zagoury
  int height(AVLNode<T>* node);

  //Nitay V
  int balanceFactor(AVLNode<T>* node);

  //Zagoury
  AVLNode<T>* minValueNode(AVLNode<T>* node);

  //Nitay V
  shared_ptr<AVLNode<T>> insert(shared_ptr<AVLNode<T>> node, T data);

  //Nitay V
  shared_ptr<AVLNode<T>> deleteNode(shared_ptr<AVLNode<T>> node, T data);


public:
  AVLTree<T>():root(nullptr){};

  //Nitay V
  virtual ~AVLTree<T>() {
    delete root.get();
  };

  //Nitay V
  bool insert(T data);

  //Zagoury
  T search(T data);

  //Nitay V
  bool deleteNode(T data);
};


template<class T>
int AVLTree<T>::height(AVLNode<T>* node)
{
  if (node == nullptr)
    return 0;
  return node->height;
}

template<class T>
int AVLTree<T>::balanceFactor(AVLNode<T>* node)
{
  if (node == nullptr)
    return 0;
  return height(node->left) - height(node->right);
}

template<class T>
bool AVLTree<T>::insert(T data){
  if (this->root == nullptr){
    this->root = make_shared<AVLNode<T>>(data);
  }
  if (this->root.data() > data){
    this->insert(this->root->left(), data);
  } else if (this->root.data() < data){
    this->insert(this->root->right(), data);
  } else {
    return false;
  }

}

template<class T>
bool AVLTree<T>::deleteNode(T data) {
  if (this->root == nullptr) return false;

  if (this->root->data() == data) {
    this->root = nullptr;
    return true;
  }

  if (this->root->data() > data) return deleteNode(this->root->left(), data);

  return deleteNode(this->root->right(), data);
}

template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::deleteNode(shared_ptr<AVLNode<T>> node, T data) {
  if (node == nullptr) return false;

  if (node->data() > data) {
    node->left = deleteNode(node->left, data);
  } else if (node->data() < data) {
    node->right = deleteNode(node->right, data);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      shared_ptr<AVLNode<T>> subTree = node->left== nullptr ? node->right: node->left;
      //if it has no child
      if (subTree == nullptr) {
        subTree = node;
        node = nullptr;
      } else {
        // if it has 1 child
        node = subTree;
      }
    } else {
      // Node has 2 children
      // switch between the smallest right son and node
      shared_ptr<AVLNode<T>> smallest_right_successor = minValueNode(node->right);
      node->data = smallest_right_successor->data;
      node->right = deleteNode(node->right, smallest_right_successor->data);
    }

    if (node == nullptr) return nullptr;

    // Get balance factor
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = balanceFactor(node);

    // Rotate if needed:

    // LL
    if (balance > 1 && balanceFactor(node->left) >= 0) return rotateRight(node);

    // RR
    if (balance < -1 && balanceFactor(node->right) <= 0) return rotateLeft(node);

    // LR
    if (balance > 1 && balanceFactor(node->left) < 0) {
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }

    // RL
    if (balance < -1 && balanceFactor(node->right) > 0) {
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }
  }
  return node;
}


template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::insert(shared_ptr<AVLNode<T>> node, T data){
  if (node == nullptr){
    return make_shared<AVLNode<T>>(data);
  }

  // recursive insertion of the new node
  if (data < node->data())
    node->left = insert(node->left, data);
  else if (data > node->data())
    node->right = insert(node->right, data);
  else
    return node;

  //update balance factor of this node
  node->height = 1 + max(height(node->left()), height(node->right()));
  int nodeBalanceFactor = this->balanceFactor(node);

  //Check the need for rotations:

  //  RR
  if (nodeBalanceFactor < -1 && data > node->right->data()){
    return rotateLeft(node);
    // LL
  } else if (nodeBalanceFactor > 1 && data < node->left->data()){
    return rotateRight(node);
    // RL
  } else if (nodeBalanceFactor < -1 && data < node->right->data()){
    node->right = rightRotate(node->right);
    return leftRotate(node);
    // LR
  } else if (nodeBalanceFactor > 1 && data > node->left->data()){
    node->right = leftRotate(node->left);
    return rightRotate(node);
  } else {
    return node;
  }
}


template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::rotateRight(AVLNode<T> *node) {
  //make rotation
  shared_ptr<AVLNode<T>> LRsubTree = node->right()->left();
  shared_ptr<AVLNode<T>> LNode = node->right();

  node->left = LRsubTree;
  LNode->right = node;

  //update heights
  node->height = 1 + max(height(node->left()), height(node->right()));
  LNode->height = 1 + max(height(node->left()), height(node->right()));

  return LNode;
}



#endif //AVLTREE_H
