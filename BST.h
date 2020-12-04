#ifndef BST_H
#define BST_H

#include "TreeNode.h"
using namespace std;

//creating the BST template class
template <class T>
class BST{
public:
//declaring functionality
  BST();
  virtual ~BST();
  void insert(T &value);
//declaring and implamenting functionality
  TreeNode<T>* getRoot() { return root; };
  void setRoot(TreeNode<T>* node) {  root=node; };
  void printTree(ofstream* outStream, TreeNode<T>* node);
//Using recursion for making printing constructor
  void printAscending()
  {
      TreeNode<T>* node = getRoot();
      if (node == NULL) return;
// first recursion on left child
      printAscending(node->left);
//printing the data of node
      node->printInfo();
// now recursion on right child
      printAscending(node->right);
  };
//Using recursion for making printing overloaded constructor
  void printAscending(TreeNode<T> * node)
  {
      if (node == NULL) return;
// first recur on left child
      printAscending(node->left);
//then print the data of node
        node->printInfo();
// now recur on right child
      printAscending(node->right);
  };


  //search function
  bool contains(int value, TreeNode<T>* node){
    if (node == NULL)
        return false;
    int tempId = node->data.getID();
    if( tempId==value)
    {
      targetNode = node;


      return true;
    }
    else if(tempId>value)
    {
        return contains(value,node->left);
    }
    else if(tempId< value)
    {
        return contains(value,node->right);
    }
  };
  //recursave call
  bool callContains(int value){return contains(value, getRoot());};
  TreeNode<T>* deleteNode(TreeNode<T>* node, int key);

  TreeNode<T>* getSuccessor(TreeNode<T>* d);

  bool deleteRec();
//Grabs minimume value of tree by going all the way to left node
  TreeNode<T>* getMin(){

      TreeNode<T>* current = getRoot();
      while (current->left != NULL)
      {
          current = current->left;
      }
      return(current);
  };
//Grabs maximum value of tree by going all the way to right node
  TreeNode<T>* getMax()
  {
      // loop down to find the rightmost leaf
      TreeNode<T>* current = getRoot();
      while (current->right != NULL)
          current = current->right;
      return (current);
  };
  bool isEmpty();
  void printTree();
//method for selcting suspific node
  TreeNode<T> *getTargetNode(){
    return targetNode;
  }
private:
  TreeNode<T> *root;
  TreeNode<T> *targetNode;
};

template <class T>
BST<T>::BST() //default constructor
{
//empty tree
  root = NULL;
  targetNode = NULL;
};
//destructor
template <class T>
BST<T>::~BST()
{
  //iterate and delete
  //need to add here
}

template <class T>
void BST<T>::printTree()
{
  recPrint(root);
}

template <class T>
bool BST<T>::isEmpty()
{
  return (root == NULL);
}

template <class T>
void BST<T>::insert(T &value)
{
  // checks if value exists, use contains(), if DNE then continue
  //setting key to value
  TreeNode<T> *node = new TreeNode<T>(value);
  if(isEmpty())   //empty tree
  {
    root = node;
  }
//not an empty tree, need to find insertion point
  else
  {
    TreeNode<T> *current = root;
    TreeNode<T> *parent;

    while(true)
    {
      parent = current;

      if (node->data < current->data)
      {
        current = current->left;
//Currant insertion point
        if(current==NULL)
        {
          parent->left = node;
          break;
        }

      }
      else
      {
        current = current->right;

        if(current==NULL)
        {
          parent->right = node;
          break;
        }
      }
    }
  }
}

//Delete functionality
template <class T>
TreeNode<T>* BST<T>::deleteNode(TreeNode<T>*  node, int key)
{

    // base case
    if (node == NULL)
    {
        return node;
    }
    // If the key to be deleted is smaller than the root's key
    if (key < node->data.getID())
    {
        node->left = deleteNode(node->left, key);
    }
    // If the key to be deleted is greater than the root's key
    else if (key > node->data.getID())
    {
        node->right = deleteNode(node->right, key);
    }
    // if key is same as root's key
    else {
        // node with only one child or no child
        if (node->left == NULL) {
            TreeNode<T>* temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL) {
            TreeNode<T>* temp = node->left;
            free(node);
            return temp;
        }

        // node with two children
        TreeNode<T>* temp  = getMin();
        node->data = temp->data;
        node->right = deleteNode(node->right, temp->data.getID());
    }
    return node;
}
template <class T>
void BST<T>::printTree(ofstream* outStream, TreeNode<T>* node)
{
    if(node==NULL)
    {
        return;
    }
    node->printNode(outStream);

    printTree(outStream, node->left);
    printTree(outStream, node->right);
}

#endif
