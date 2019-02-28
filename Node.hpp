//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
//  Modified by Tiziana Ligorio 2019 for CSCI 235 Hunter College

/** @file Node.h
    Listing 4-1 */
#ifndef NODE_
#define NODE_

template<class T>
class Node
{
public:
   Node();
   Node(const T& an_item_);
   Node(const T& an_item, Node<T>* next_node_ptr);
   void setItem(const T& an_item);
   void setNext(Node<T>* next_node_ptr);
   T getItem() const ;
   Node<T>* getNext() const ;

 private:
    T item_; // A data item_
    Node<T>* next_; // Pointer to next_ node
}; // end Node

#include "Node.cpp"
#endif
