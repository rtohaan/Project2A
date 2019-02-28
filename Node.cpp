//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
//  Modified by Tiziana Ligorio 2019 for CSCI 235 Hunter College

/** @file Node.cpp
    Listing 4-2 */
#include "Node.hpp"
//#include <cstddef>

template<class T>
Node<T>::Node() : next_(nullptr)
{
} // end default constructor

template<class T>
Node<T>::Node(const T& an_item) : item_(an_item), next_(nullptr)
{
} // end constructor

template<class T>
Node<T>::Node(const T& an_item, Node<T>* next_node_ptr) :
                item_(an_item), next_(next_node_ptr)
{
} // end constructor

template<class T>
void Node<T>::setItem(const T& an_item)
{
   item_ = an_item;
} // end setItem

template<class T>
void Node<T>::setNext(Node<T>* next_node_ptr)
{
   next_ = next_node_ptr;
} // end setNext

template<class T>
T Node<T>::getItem() const
{
   return item_;
} // end getItem

template<class T>
Node<T>* Node<T>::getNext() const
{
   return next_;
} // end getNext
