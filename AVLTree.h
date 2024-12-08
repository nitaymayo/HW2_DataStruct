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

  AVLNode(T k):value(k),left_child(nullptr),right_child(nullptr),height(1){}

  shared_ptr<AVLNode<T>> left() const{
    return left;
  }
  shared_ptr<AVLNode<T>> right() const{
    return right;
  }
};

template<class T>
class AVLTree {
private:
  shared_ptr<AVLNode<T>> root;

  //Zagoury
  shared_ptr<AVLNode<T>> rotateLeft(AVLNode<T> *node);

  //Nitay
  shared_ptr<AVLNode<T>> rotateRight(AVLNode<T> *node);

  //Zagoury
  int height(AVLNode<T>* node);

  //Nitay
  int balanceFactor(AVLNode<T>* node);

  //Zagoury
  AVLNode<T>* minValueNode(AVLNode<T>* node);

  //Nitay V
  shared_ptr<AVLNode<T>> insert(shared_ptr<AVLNode<T>> node, T data);

public:
  AVLTree<T>():root(nullptr){};

  //Nitay
  ~AVLTree<T>();

  //Nitay
  bool insert(T data);

  //Zagoury
  T search(T data);

  //Nitay
  bool deleteTree(T data);
};



#endif //AVLTREE_H
