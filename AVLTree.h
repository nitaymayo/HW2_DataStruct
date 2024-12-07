//
// Created by nitaymayo on 12/7/24.
//

#ifndef AVLTREE_H
#define AVLTREE_H



template<class T>
class AVLNode {
public:
  int key;
  T value;
  AVLNode* left;
  AVLNode* right;
  int height;

  AVLNode(T k):key(k),left(nullptr),right(nullptr),height(1){}
};

template<class T>
class AVLTree<T> {
private:
  AVLNode<T>* root;

  //Zagoury
  bool rotateLeft(AVLNode<T> *node);

  //Nitay
  bool rotateRight(AVLNode<T> *node);

  //Zagoury
  int height(AVLNode<T>* node);

  //Nitay
  int balanceFactor(AVLNode<T>* node);

  //Zagoury
  AVLNode<T>* minValueNode(AVLNode<T>* node)

public:
  AVLTree<T>():root(nullptr){};

  //Nitay
  ~AVLTree<T>();

  //Nitay
  bool insert(T data);

  //Zagoury
  T search(T data);

  //Nitay
  bool delete(T data);
};



#endif //AVLTREE_H
