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

  RedBlackNode<KeyType,ValueType>* getUncle() const
  {
    if(getGrandParent() == NULL)
      return NULL;
    auto grandparent = getGrandParent();
    auto uncle = grandparent->getKey() > Node<KeyType, ValueType>::getKey() ? grandparent->getRight() : grandparent->getLeft();
    return static_cast<RedBlackNode<KeyType,ValueType>*>(uncle);
  }

  RedBlackNode<KeyType,ValueType>* getGrandParent() const{
    if(Node<KeyType, ValueType>::getParent() == NULL)
      return NULL;
    return static_cast<RedBlackNode<KeyType,ValueType>*>(Node<KeyType, ValueType>::getParent()->getParent());
  }
  
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
     (with a possibly differ
     ent associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */
  {

    RedBlackNode<KeyType,ValueType>* node = new RedBlackNode<KeyType,ValueType>(new_item.first, new_item.second, NULL);
    BinarySearchTree<KeyType, ValueType>::insert(node);

    std::cout << "Inserting "<<new_item.first << std::endl;
    fixRBTree(static_cast<RedBlackNode<KeyType,ValueType>*>(node));
    print();
  }

  void fixRBTree(RedBlackNode<KeyType,ValueType>* rbnode){
    while(rbnode != BinarySearchTree<KeyType, ValueType>::root){
      auto parent = rbnode->getParent();

      //Parent is red
      if(parent->getColor() != black){ 
        auto uncle = rbnode->getUncle();
        auto grandparent = rbnode->getGrandParent();
        if(grandparent != NULL){
          if(uncle != NULL && uncle->getColor() == red){ 
            //Uncle is red case
            parent->setColor(black);
            uncle->setColor(black);
            grandparent->setColor(red);

          } else { 
            //Uncle is black cases
            std::cout << "Black case" << std::endl;

            //Left Left case
            if(parent->getKey() < grandparent->getKey() && rbnode->getKey() < parent->getKey()){
              std::cout << "left left case" << std::endl;
              rotateRight(grandparent);
              parent->setColor(black);
              grandparent->setColor(red);
            } 
            //Left Right case
            else if(parent->getKey() < grandparent->getKey() && rbnode->getKey() > parent->getKey()){
              std::cout << "left right case" << std::endl;
              rotateLeft(parent);
              rotateRight(grandparent);
              parent->setColor(black);
              grandparent->setColor(red);
            }
            //Right Right case
            else if(parent->getKey() > grandparent->getKey() && rbnode->getKey() > parent->getKey()){
              std::cout << "right right case" << std::endl;
              rotateLeft(grandparent);
              grandparent->setColor(red);
              parent->setColor(black);
            }

            //Right Left case
            else if(parent->getKey() > grandparent->getKey() && rbnode->getKey() < parent->getKey()){
              std::cout << "right left case" << std::endl;
              rotateRight(parent);
              rotateLeft(grandparent);
              grandparent->setColor(red);
              parent->setColor(black);
            }
          }
          rbnode = grandparent;
        }
        
        else{
          rbnode = parent; //set rbnode to root
        }
      }

      rbnode = parent;
      //node = rbnode;
    }

    //RBnode is root
    if(rbnode->getParent() == NULL)
      rbnode->setColor(black);
    
  }


  void print () const
  { 
    printRoot (BinarySearchTree<KeyType, ValueType>::root);
    std::cout << "\n";
  }

  /**
   * Helper function to print the tree's contents
   */
  virtual void printRoot (Node<KeyType, ValueType> *r) const
  {
    if (r != NULL)
      {
        auto * rb = static_cast<RedBlackNode<KeyType,ValueType>*>(r);
        std::cout << "[";
        printRoot (r->getLeft());
        auto color = rb->getColor() == black?"black":"red";
        std::cout << " (" << r->getKey() << ", " << r->getValue() << ", " << color << ") ";
        printRoot (r->getRight());
        std::cout << "]";
      }
  }

private:

  /*Helper functions*/

  //Left and right rotations
  void rotateLeft(Node<KeyType, ValueType> * x){
    auto y = x->getRight();
    if(y == NULL)
      return;

    x->setRight(y->getLeft());

    if(y->getLeft() != NULL){
      y->getLeft()->setParent(x);
    }

    y->setLeft(x);


    y->setParent(x->getParent());
    x->setParent(y);
    if(y->getParent() == NULL){
      BinarySearchTree<KeyType, ValueType>::root = y;
    } else {
      auto parent = y->getParent();
      if(parent->getKey() < y->getKey())
        parent->setRight(y);
      else
        parent->setLeft(y);
    }

  }
  void rotateRight(Node<KeyType, ValueType> * z){
    auto y = z->getLeft();
    if(y == NULL)
      return;

    z->setLeft(y->getRight());

    if(z->getLeft() != NULL){
      z->getLeft()->setParent(z);
    }

    y->setRight(z);

    y->setParent(z->getParent());
    z->setParent(y);
    if(y->getParent() == NULL){
      BinarySearchTree<KeyType, ValueType>::root = y;
    } else {
      auto parent = y->getParent();
      if(parent->getKey() < y->getKey())
        parent->setRight(y);
      else
        parent->setLeft(y);
    }


  }


};



#endif
