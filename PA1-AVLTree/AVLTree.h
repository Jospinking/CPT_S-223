/*
 *  Yet another AVL tree edition
 *
 *  Contributors:
 *      Aaron S. Crandall <acrandal@wsu.edu> - 2018
 *
 */

#ifndef __AVLTree_H
#define __AVLTree_H

#include <ostream>
#include <algorithm>     // Includes a max(a,b) function
#include <exception>

#include "AVLNode.h"

// AVLTree class
// ******************PUBLIC OPERATIONS*********************
// bool empty( )          --> Test for empty tree
// int size( )            --> Quantity of elements in tree
// int height( )          --> Height of the tree (nullptr == -1)
// void add( x )          --> Insert new value x
// void remove( x )       --> Remove node with value x
// void clear ( )         --> Removes all elements from tree
// bool contains( x )     --> Return true if x is present
// T findMin( )           --> Return smallest item value
// T findMax( )           --> Return largest item value
// void printPreOrder( )  --> Print tree in pre order to an ostream
// void ~AVLTree( )       --> Big Five Destructor
// AVLTree( )             --> Basic constructor


template <typename T>
class AVLTree
{
private:
    AVLNode<T> * _root;

public:
    AVLTree() : _root(nullptr) {}    // initializes root to nullptr

    /* Returns true if the tree is empty */
    bool empty() {
        // TODO: Properly return t/f if the tree is empty or not
        if (_root == nullptr)
        return true;
        return false;
      }

    void add(const T & newVal) {
        // TODO: implement adding a value to the tree
        _root = insert (_root, newVal);

    }

    void remove(const T & remVal) {
        // TODO: Implemente properly removing a node and rebalancing the tree
        _root = deleteNode(_root, remVal);
    }

    void clear() {
        // TODO: Delete all elements in the tree
        deleteTree(_root);
        _root = nullptr;
    }

    bool contains(const T & findVal) {
        // TODO: Return t/f if a given value is currently in the tree
        AVLNode<T>* current = _root;
        while (current != nullptr){
          if (findVal == current->val)
            return true;
          if (findVal > current->val)
          current = current->right;
          else
          current = current ->left;
        }

        return false;
    }

    int height() {
        // TODO: Return the current height of the tree
        // Remember! A null pointer is height -1
        if (_root == nullptr)
          return -1;
        return height (_root);
    }

    T findMin() {
        if (_root == nullptr)
          return 0;

           // this is to allow the tests to fail - should definitely be changed!

        AVLNode<T>* current = _root;


        while (current->left != nullptr)
          current = current->left;

          return current->val;  // Return the minimum *value* in the tree (not a tree node)

    }

    T findMax() {
        // Return the maximum *value* in the tree (not a tree node)
        if (_root == nullptr)
          return 0;

        // this is to allow the tests to fail - should definitely be changed!

        AVLNode<T>* current = _root;


        while (current->right != nullptr)
          current = current->right;

        return current->val;

    }

    // Prints the tree to ostream out in preorder traversal
    void printPreOrder(std::ostream& out) {
        printPreOrder(this->_root, out);
    }

    int size() {
        // TODO: Return the size of the tree (number of nodes in the tree)
        return size (_root);

    }

// *************** Private /internal function implementation ******* //

private:
    // Should put your various internal balancing, rotating, and calculating functions here
    AVLNode<T> * rightRotate(AVLNode<T> * y)
   {
       AVLNode<T> *x = y->left;
       AVLNode<T> *T2 = x->right;

       x->right = y;
       y->left = T2;

       y->height = std::max(height(y->left), height(y->right))+1;
       x->height = std::max(height(x->left), height(x->right))+1;

       return x;
   }

   AVLNode<T> *leftRotate(AVLNode<T> *x)
   {
       AVLNode<T> *y = x->right;
       AVLNode<T> *T2 = y->left;

       y->left = x;
       x->right = T2;

       x->height = std::max(height (x->left), height(x->right))+1;
       y->height = std::max(height(y->left), height(y->right))+1;

       return y;
   }

   int getBalance(AVLNode<T> *N)
   {
       if (N == nullptr)
           return 0;
       return height(N->left) - height(N->right);
   }

   AVLNode<T> * insert(AVLNode<T> *node, const T & val)
   {
       if (node == nullptr)
           return new AVLNode<T>(val);

       if (val < node->val)
           node->left  = insert(node->left, val);
       else if (val > node->val)
           node->right = insert(node->right, val);
       else
           return node;

       node->height = 1 + std::max(height(node->left), height(node->right));


       int balance = getBalance(node);


       if (balance > 1 && val< node->left->val)
           return rightRotate(node);

       if (balance < -1 && val > node->right->val)
           return leftRotate(node);

       if (balance > 1 && val > node->left->val)
       {
           node->left =  leftRotate(node->left);
           return rightRotate(node);
       }

       if (balance < -1 && val < node->right->val)
       {
           node->right = rightRotate(node->right);
           return leftRotate(node);
       }

       return node;
   }

   AVLNode<T>* minValueNode(AVLNode<T>* node)
   {
       AVLNode<T>* current = node;

       while (current->left != NULL)
           current = current->left;

       return current;
   }

   AVLNode<T>* deleteNode(AVLNode<T>* root, const T & val)
   {

       if (root == nullptr)
           return root;


       if ( val < root->val )
           root->left = deleteNode(root->left, val);


       else if( val > root->val )
           root->right = deleteNode(root->right, val);


       else
       {
           if( (root->left == nullptr) || (root->right == nullptr) )
           {
               AVLNode<T> *temp = root->left ? root->left :
                                                root->right;

               if (temp == nullptr)
               {
                   temp = root;
                   root = nullptr;
               }
               else
                *root = *temp;
               delete temp;
           }
           else
           {

               AVLNode<T>* temp = minValueNode(root->right);

               root->val = temp->val;

               root->right = deleteNode(root->right, temp->val);
           }
       }

       if (root == nullptr)
         return root;

       root->height = 1 + std::max(height(root->left), height(root->right));


       int balance = getBalance(root);

       // Rotations:

       // Left Left
       if (balance > 1 && getBalance(root->left) >= 0)
           return rightRotate(root);

       // Left Right
       if (balance > 1 && getBalance(root->left) < 0)
       {
           root->left =  leftRotate(root->left);
           return rightRotate(root);
       }

       // Right Right
       if (balance < -1 && getBalance(root->right) <= 0)
           return leftRotate(root);

       // Right Left
       if (balance < -1 && getBalance(root->right) > 0)
       {
           root->right = rightRotate(root->right);
           return leftRotate(root);
       }

       return root;
   }

  void deleteTree(AVLNode<T>* & node)
   {
       if (node == nullptr) {
           return;
       }

       deleteTree(node->left);
       deleteTree(node->right);

       delete node;
   }

  int size(AVLNode<T>* node){
       if (node==nullptr)
           return 0;
       else
           return(size(node->left) + 1 + size(node->right));
   }


    // Freebie: neat little function to safely get a node's height
    int height( AVLNode<T> * t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    // Traverses the tree and prints in pre order
    // This is used a lot in the testing system, changing it would be troublesome
    void printPreOrder(AVLNode<T> * & t, std::ostream& out)
    {
        if( t != nullptr )
        {
            out << t->val << " ";
            printPreOrder(t->left, out);
            printPreOrder(t->right, out);
        }
    }



};




#endif
