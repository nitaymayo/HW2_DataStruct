#include "AVLTree.h"
#include <stdlib.h>
#include <stdio.h>


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
     if (nodeBalanceFactor < -1 && data > node->right()->data()){
       return rotateLeft(node);
       // LL
     } else if (nodeBalanceFactor > 1 && data < node->left()->data()){
       return rotateRight(node);
       // RL
     } else if (nodeBalanceFactor < -1 && data < node->right->data()){
       node->right = rightRotate(node->right);
       return leftRotate(node);
       // LR
     } else if (nodeBalanceFactor > 1 && data > node->left()->data()){
       node->right = leftRotate(node->left);
       return rightRotate(node);
     } else {
       return node;
     }
}