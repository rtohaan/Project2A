//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
//  Modified by Tiziana Ligorio 2019 for CSCI 235 Hunter College

// Kenneth Chen
// 2/27/19
/** ADT bag: Link-based implementation.
    @file LinkedBag.cpp */

#include "LinkedBag.hpp"
#include "Node.hpp"
#include <cstddef>

template<class T>
LinkedBag<T>::LinkedBag() : head_ptr_(nullptr), item_count_(0)
{
}  // end default constructor

template<class T>
LinkedBag<T>::LinkedBag(const LinkedBag<T>& a_bag)
{
	item_count_ = a_bag.item_count_;
   Node<T>* orig_chain_ptr = a_bag.head_ptr_;  // Points to nodes in original chain

   if (orig_chain_ptr == nullptr)
      head_ptr_ = nullptr;  // Original bag is empty
   else
   {
      // Copy first node
      head_ptr_ = new Node<T>();
      head_ptr_->setItem(orig_chain_ptr->getItem());

      // Copy remaining nodes
      Node<T>* new_chain_ptr = head_ptr_;      // Points to last node in new chain
      orig_chain_ptr = orig_chain_ptr->getNext();     // Advance original-chain pointer

      while (orig_chain_ptr != nullptr)
      {
         // Get next item from original chain
         T next_item = orig_chain_ptr->getItem();

         // Create a new node containing the next item
         Node<T>* new_node_ptr = new Node<T>(next_item);

         // Link new node to end of new chain
         new_chain_ptr->setNext(new_node_ptr);

         // Advance pointer to new last node
         new_chain_ptr = new_chain_ptr->getNext();

         // Advance original-chain pointer
         orig_chain_ptr = orig_chain_ptr->getNext();
      }  // end while

      new_chain_ptr->setNext(nullptr);              // Flag end of chain
   }  // end if
}  // end copy constructor

template<class T>
LinkedBag<T>::~LinkedBag()
{
   clear();
}  // end destructor

template<class T>
bool LinkedBag<T>::isEmpty() const
{
	return item_count_ == 0;
}  // end isEmpty

template<class T>
int LinkedBag<T>::getCurrentSize() const
{
    return item_count_;
}  // end getCurrentSize

template<class T>
bool LinkedBag<T>::add(const T& new_entry)
{
   // Add to beginning of chain: new node references rest of chain;
   // (head_ptr_ is null if chain is empty)
   Node<T>* next_node_ptr = new Node<T>();
   next_node_ptr->setItem(new_entry);
   next_node_ptr->setNext(head_ptr_);  // New node points to chain
//   Node<T>* next_node_ptr = new Node<T>(new_entry, head_ptr_); // alternate code

   head_ptr_ = next_node_ptr;          // New node is now first node
   item_count_++;

   return true;
}  // end add


template<class T>
std::vector<T> LinkedBag<T>::toVector() const
{
   std::vector<T> bag_contents;
   Node<T>* cur_ptr = head_ptr_;
	while ((cur_ptr != nullptr))
   {
		bag_contents.push_back(cur_ptr->getItem());
        cur_ptr = cur_ptr->getNext();
   }  // end while

   return bag_contents;
}  // end toVector

template<class T>
bool LinkedBag<T>::remove(const T& an_entry)
{
   Node<T>* entry_node_ptr = getPointerTo(an_entry);
   bool can_remove = !isEmpty() && (entry_node_ptr != nullptr);
   if (can_remove)
   {
      // Copy data from first node to located node
      entry_node_ptr->setItem(head_ptr_->getItem());

      // Delete first node
      Node<T>* node_to_delete = head_ptr_;
      head_ptr_ = head_ptr_->getNext();

      // Return node to the system
      node_to_delete->setNext(nullptr);
      delete node_to_delete;
      node_to_delete = nullptr;

      item_count_--;
   } // end if

	return can_remove;
}  // end remove


template<class T>
void LinkedBag<T>::clear()
{
   Node<T>* node_to_delete = head_ptr_;
   while (head_ptr_ != nullptr)
   {
      head_ptr_ = head_ptr_->getNext();

      // Return node to the system
      node_to_delete->setNext(nullptr);
      delete node_to_delete;

      node_to_delete = head_ptr_;
   }  // end while
   // head_ptr_ is nullptr; node_to_delete is nullptr

	item_count_ = 0;
}  // end clear


template<class T>
int LinkedBag<T>::getFrequencyOf(const T& an_entry) const
{
	int frequency = 0;
   int counter = 0;
   Node<T>* cur_ptr = head_ptr_;
   while ((cur_ptr != nullptr) && (counter < item_count_))
   {
      if (an_entry == cur_ptr->getItem())
      {
         frequency++;
      } // end if

      counter++;
      cur_ptr = cur_ptr->getNext();
   } // end while

	return frequency;
}  // end getFrequencyOf

template<class T>
bool LinkedBag<T>::contains(const T& an_entry) const
{
	return (getPointerTo(an_entry) != nullptr);
}  // end contains

/**
 @param a_bag to be combined with the contents of this (the calling) bag
 @return a new LinkedBag that contains all elements from this
 bag (items_)and from a_bag. Note that it may contain duplicates
*/
template<class T>
LinkedBag<T> LinkedBag<T>::bagUnion(const LinkedBag<T>& a_bag) const
{
	LinkedBag<T> UnionBag;
	Node<T>* c_ptr = head_ptr_;							// creates a current ptr to the current bag's head ptr
	Node<T>* a_bag_c_ptr = a_bag.head_ptr_;				// creates a 2nd current ptr for a_bag's head ptr
	for(int i = 0; i < getCurrentSize(); i++)
	{
		UnionBag.add(c_ptr->getItem());					// loops through the bag and adds it to the front of union bag
		c_ptr = c_ptr->getNext();
	}
	for(int j = 0; j < a_bag.getCurrentSize(); j++)	
	{
		UnionBag.add(a_bag_c_ptr->getItem());			// loops through a_bag and adds it to the front of unionbag
		a_bag_c_ptr = a_bag_c_ptr->getNext();
	}
	return UnionBag;
}

/**
 @param a_bag to be intersected with the contents of this (the calling)
 bag
 @return a new LinkedBag that contains the intersection of the contents
 of this bag and those of the argument a_bag. This intersection does not
 contain duplicates (e.g. every element occurring in BOTH bags will be
 found only once in the intersection, no matter how many occurrences in
 the original bags) as in set intersection A n B
 */
template<class T>
LinkedBag<T> LinkedBag<T>::bagIntersectionNoDuplicates(const LinkedBag<T>& a_bag) const
{
	LinkedBag<T> InterBag;
	Node<T>* c_ptr = head_ptr_;																		// creates a current ptr to the current bag's head ptr
	for(int i = 0; i < getCurrentSize(); i++)
	{
		if(!InterBag.contains(c_ptr->getItem()) && a_bag.contains(c_ptr->getItem()))				// loops through the bag and checks if InterBag does not have the
		{																							// value and then checks if a_bag contains the value, if both
			InterBag.add(c_ptr->getItem());															// conditions are met, add it to the InterBag
		}	
		c_ptr = c_ptr->getNext();
	}
	return InterBag;
}

/**
 @param a_bag to be subtracted from this bag
 @return a new LinkedBag that contains only those items that occur in
 this bag or in a_bag but not in both, and it does not contain duplicates
 */
template<class T>
LinkedBag<T> LinkedBag<T>::bagDifference(const LinkedBag<T>& a_bag) const
{
	LinkedBag<T> DiffBag;
	Node<T>* c_ptr = head_ptr_;																				// creates a current ptr to the current bag's head ptr
	Node<T>* a_bag_c_ptr = a_bag.head_ptr_;																	// creates a 2nd current ptr for a_bag's head ptr
	for(int i = 0; i < getCurrentSize(); i++)
	{
		if(!DiffBag.contains(c_ptr->getItem()) && !a_bag.contains(c_ptr->getItem()))						// loops through the bag and checks if a_bag also has the
		{																									// same value, if a_bag doesnt contain it, add it to 
			DiffBag.add(c_ptr->getItem());																	// DiffBag
		}
		c_ptr = c_ptr->getNext();
	}
	for(int j = 0; j < a_bag.getCurrentSize(); j++)
	{
		if(!DiffBag.contains(a_bag_c_ptr->getItem()) && !contains(a_bag_c_ptr->getItem()))					// loops through a_bag and checks if the bag also has the
		{																									// same value, if the bag doesn't contain it, add it to
			DiffBag.add(a_bag_c_ptr->getItem());															// DiffBag
		}
		a_bag_c_ptr = a_bag_c_ptr->getNext();
	}
	return DiffBag;
}

/**
 @param a_bag whose contents are to be copied to this (the calling) bag
 @post this (the calling) bag has same contents as a_bag
*/
template<class T>
void LinkedBag<T>::operator=(const LinkedBag<T>& a_bag)
{
	Node<T>* a_bag_c_ptr = a_bag.head_ptr_;							// creates a ptr for a_bag's head ptr
	clear();														// clears the bag
	for(int i = 0; i < a_bag.getCurrentSize(); i++)
	{
		add(a_bag_c_ptr->getItem());								// copies a_bag's contents into the bag
		a_bag_c_ptr = a_bag_c_ptr->getNext();
	}
}

/**
 @param new_entry to be added to the bag
 @post new_entry is added at the end of the chain preserving the order of
 items in the bag
 @return true if added successfully, false otherwise
 */
template<class T>
bool LinkedBag<T>::addToEnd(const T& new_entry)
{
	Node<T>* end_ptr = head_ptr_;									// creates a ptr to the head_ptr
	for(int i = 0; i < getCurrentSize()-1; i++)						// loops through the bag until its 1 before nullptr
	{
		end_ptr->getNext();											// gets the next node
	}
	Node<T>* new_node = new Node<T>(new_entry);						// creates a new node with an item value "new_entry"
	end_ptr->setNext(new_node);										// sets the next node's ptr using new_node's head_ptr
	end_ptr->setItem(new_entry);									// sets the node's entry
	new_node->setNext(nullptr);										// sets back the next ptr to point to nullptr to signify the end
}


// private


/**
 @return Returns either a pointer to the node containing a given entry
 or the null pointer if the entry is not in the bag.
 */
template<class T>
Node<T>* LinkedBag<T>::getPointerTo(const T& an_entry) const
{
    bool found = false;
    Node<T>* cur_ptr = head_ptr_;

    while (!found && (cur_ptr != nullptr))
    {
        if (an_entry == cur_ptr->getItem())
            found = true;
        else
            cur_ptr = cur_ptr->getNext();
    } // end while

    return cur_ptr;
} // end getPointerTo

