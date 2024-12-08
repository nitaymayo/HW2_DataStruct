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

  explicit AVLNode(T k):value(k),left(nullptr),right(nullptr),height(1){}

  virtual ~AVLNode() {
    delete left.get();
    delete right.get();
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
  shared_ptr<AVLNode<T>> rotateLeft(shared_ptr<AVLNode<T>> node);

  //Nitay V
  shared_ptr<AVLNode<T>> rotateRight(shared_ptr<AVLNode<T>> node);

  //Zagoury
  int height(shared_ptr<AVLNode<T>> node);

  //Nitay V
  int balanceFactor(shared_ptr<AVLNode<T>> node);

  //Zagoury
  AVLNode<T>* minValueNode(AVLNode<T>* node);

  //Nitay V
  shared_ptr<AVLNode<T>> insert(shared_ptr<AVLNode<T>> node, T data);

  //Nitay V
  shared_ptr<AVLNode<T>> deleteNode(shared_ptr<AVLNode<T>> node, T data);



  void printInorder(shared_ptr<AVLNode<T>> root)
  {
    if (root != nullptr) {
      printInorder(root->left);
      cout << root->data() << " ";
      printInorder(root->right);
    }
  }

public:
  AVLTree():root(nullptr){};

  //Nitay V
  virtual ~AVLTree() {
    delete root.get();
  };

  //Nitay V
  bool insert(T data);

  //Zagoury
  T search(T data);

  //Nitay V
  bool deleteNode(T data);

  void printInorder() {
    if (root != nullptr) {
      printInorder(root->left);
      cout << root->data() << " ";
      printInorder(root->right);
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
bool AVLTree<T>::insert(T data){
  if (this->root == nullptr){
    this->root = make_shared<AVLNode<T>>(data);
    return true;
  }
  try {
    if (this->root->data() > data){
      this->insert(this->root->left, data);
    } else if (this->root->data() < data){
      this->insert(this->root->right, data);
    } else {
      return false;
    }
  } catch (logic_error &e) {
    return false;
  }
  return true;

}

template<class T>
shared_ptr<AVLNode<T>> AVLTree<T>::insert(shared_ptr<AVLNode<T>> node, T data){
  if (node == nullptr){
    return make_shared<AVLNode<T>>(data);
  }

  if (node->data() == data) throw logic_error("data already exists");

  // recursive insertion of the new node
  if (data < node->data())
    node->left = insert(node->left, data);
  else if (data > node->data())
    node->right = insert(node->right, data);
  else
    return node;

  //update balance factor of this node
  node->height = 1 + max(height(node->left), height(node->right));
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
    node->right = rotateRight(node->right);
    return rotateLeft(node);
    // LR
  } else if (nodeBalanceFactor > 1 && data > node->left->data()){
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  } else {
    return node;
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
shared_ptr<AVLNode<T>> AVLTree<T>::rotateRight(shared_ptr<AVLNode<T>> node) {
  //make rotation
  shared_ptr<AVLNode<T>> LRsubTree = node->right->left;
  shared_ptr<AVLNode<T>> left_node = node->right;

  node->left = LRsubTree;
  left_node->right = node;

  //update heights
  node->height = 1 + max(height(node->left), height(node->right));
  left_node->height = 1 + max(height(node->left), height(node->right));

  return left_node;
}



#endif //AVLTREE_H
