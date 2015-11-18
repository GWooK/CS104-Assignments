/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 */
#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
  RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { color = red; }
  
  virtual ~RedBlackNode () {}
  
  Color getColor () const
    { return color; }
  
  void setColor (Color c)
    { color = c; }
  
  virtual RedBlackNode<KeyType, ValueType> *getParent () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_parent; }
  
  virtual RedBlackNode<KeyType, ValueType> *getLeft () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_left; }
  
  virtual RedBlackNode<KeyType, ValueType> *getRight () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_right; }
  
 protected:
  Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  void insert (const std::pair<const KeyType, ValueType>& new_item)
  /* This one is yours to implement.
     It should insert the (key, value) pair to the tree, 
     making sure that it remains a valid Red-Black Tree.
     If the key is already in the tree
     (with a possibly different associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */
  {
    auto node = BinarySearchTree<KeyType, ValueType>::insert(new_item);
  }

private:

  /*Helper functions*/

  //Left and right rotations
  void rotateLeft(Node<KeyType, ValueType> * node){
    if(node->getRight() == NULL){
      return;
    }

    Node<KeyType, ValueType> * pRight = node->getRight();
    node->setRight(pRight->getLeft());

    if(node->getParent() == NULL){
      BinarySearchTree<KeyType, ValueType>::root = pRight;
    } else if(node->getParent()->getLeft() == node){
      node->getParent()->setLeft(pRight);
    } else{
      node->getParent()->setRight(pRight);
    }

    pRight->setLeft(node);
  }
  void rotateRight(Node<KeyType, ValueType> * node){
    if(node->getLeft() == NULL){
      return;
    }

    Node<KeyType, ValueType> * pLeft = node->getLeft();
    node->setLeft(pLeft->getRight());

    if(node->getParent() == NULL){
      BinarySearchTree<KeyType, ValueType>::root = pLeft;
    } else if(node->getParent()->getLeft() == node){
      node->getParent()->setLeft(pLeft);
    } else{
      node->getParent()->setRight(pLeft);
    }

    pLeft->setRight(node);
  }



};



#endif
