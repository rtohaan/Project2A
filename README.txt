Project 2A

Implements these functions into LinkedBag.cpp and LinkedBag.hpp

 /**
 @param a_bag to be combined with the contents of this (the calling) bag
 @return a new LinkedBag that contains all elements from this
 bag (items_)and from a_bag. Note that it may contain duplicates
 */
 LinkedBag<T> bagUnion(const LinkedBag<T>& a_bag) const;

Note: this time bag size is not statically constrained as with arrays, so the union will contain all contents
of both bags.


 /**
 @param a_bag to be intersected with the contents of this (the calling)
 bag
 @return a new LinkedBag that contains the intersection of the contents
 of this bag and those of the argument a_bag. This intersection does not
 contain duplicates (e.g. every element occurring in BOTH bags will be
 found only once in the intersection, no matter how many occurrences in
 the original bags) as in set intersection A n B
 */
 LinkedBag<T> bagIntersectionNoDuplicates(const LinkedBag<T>& a_bag) const;


 /**
 @param a_bag to be subtracted from this bag
 @return a new LinkedBag that contains only those items that occur in
 this bag or in a_bag but not in both, and it does not contain duplicates
 */

 LinkedBag<T> bagDifference(const LinkedBag<T>& a_bag) const;


/**
 @param a_bag whose contents are to be copied to this (the calling) bag
 @post this (the calling) bag has same contents as a_bag
 */

void operator= (const LinkedBag<T>& a_bag);


 /**
 @param new_entry to be added to the bag
 @post new_entry is added at the end of the chain preserving the order of
 items in the bag
 @return true if added successfully, false otherwise
 */

 bool addToEnd(const T& new_entry); 