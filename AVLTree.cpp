//
// Created by nitaymayo on 12/7/24.
//

#include "AVLTree.h"


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