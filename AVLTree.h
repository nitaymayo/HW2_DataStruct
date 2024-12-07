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
  AVLNode* left; // Pointer to the left child
  AVLNode* right; // Pointer to the right child
  int height; // Height of the node in the tree

  // Constructor to initialize a node with a given key
  AVLNode(T k):key(k),left(nullptr),right(nullptr),height(1){}
};

template<class T>
class AVLTree<T> {
private:
  AVLNode<T>* root;


  bool rotateLeft(AVLNode<T> *node);
  bool rotateRight(AVLNode<T> *node);

  int height(AVLNode<T>* node);

  int balanceFactor(AVLNode<T>* node);

public:
  AVLTree<T>();

  ~AVLTree<T>();

  bool insert(T data);

  AVLNode<T>* minValueNode(AVLNode<T>* node)

  T search(T data);

  bool delete(T data);

};



#endif //AVLTREE_H
