#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <fstream>
using namespace std;

template <class T>
class TreeNode
{
public:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode();
    TreeNode(T &d);
    ~TreeNode();
    void printInfo();   //print the data stored
    void printNode(ofstream* outStream);
    bool operator < (TreeNode<T> &other);
    bool operator > (TreeNode<T> &other);
    bool operator == (TreeNode<T> &other);
};

template <class T>
TreeNode<T>::TreeNode() {
    data = T();
    left = NULL;
    right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T &d) {
    data = d;
    left = NULL;
    right = NULL;
}

template <class T>
TreeNode<T>::~TreeNode() {
    delete left;
    delete right;
    delete data;
}

template <class T>
void TreeNode<T>::printInfo() {
    data.printInfo();
}
template <class T>
void TreeNode<T>::printNode(ofstream* outStream) {
    data.printNode(outStream);
}

template <class T>
bool TreeNode<T>::operator < (TreeNode<T> &other) {
    return (*data < other.data);
}

template <class T>
bool TreeNode<T>::operator > (TreeNode<T> &other) {
    return (*data > other.data);
}

template <class T>
bool TreeNode<T>::operator == (TreeNode<T> &other) {
    return (*data == other.data);
}

#endif
