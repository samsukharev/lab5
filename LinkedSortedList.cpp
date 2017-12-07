//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Implementation file for the class LinkedSortedList.
 @file LinkedSortedList.cpp */

#include "LinkedSortedList.h"  // Header file
#include <cassert>

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(const LinkedSortedList<ItemType>& aList)
{
	headPtr = copyChain(aList.headPtr);
   itemCount = aList.itemCount;
}  // end copy constructor

template<class ItemType>
auto LinkedSortedList<ItemType>::copyChain(const std::shared_ptr<Node<ItemType>>& origChainPtr)
{
   std::shared_ptr<Node<ItemType>> copiedChainPtr;
	if (origChainPtr != nullptr)
	{
		// Build new chain from given one
      // Create new node with the current item
      copiedChainPtr = std::make_shared<Node<ItemType>>(origChainPtr->getItem());
      // have the node point to the rest of the chain
		copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));		
	}  // end if
   
	return copiedChainPtr;
}  // end copyChain

template<class ItemType>
LinkedSortedList<ItemType>::~LinkedSortedList()
{
   clear();
}  // end destructor

template<class ItemType>
bool LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry)
{
   auto newNodePtr = std::make_shared<Node<ItemType>>(newEntry); // one memory allocation
   auto prevPtr = getNodeBefore(newEntry);
   
   if (isEmpty() || (prevPtr == nullptr)) // Add at beginning
   {
      newNodePtr->setNext(headPtr);
      headPtr = newNodePtr;
   }
   else // Add after node before
   {
      auto aftPtr = prevPtr->getNext();
      newNodePtr->setNext(aftPtr);
      prevPtr->setNext(newNodePtr);
   } // end if
   
   itemCount++;
   return true;
} // end insertSorted

template<class ItemType>
bool LinkedSortedList<ItemType>::removeSorted(const ItemType& anEntry)
{
   bool ableToDelete = false;
   if (!isEmpty())
   {
      auto nodeToRemovePtr = headPtr;
      auto prevPtr = getNodeBefore(anEntry);
      if (prevPtr != nullptr)
         nodeToRemovePtr = prevPtr->getNext();
       
      ableToDelete = (nodeToRemovePtr != nullptr) && 
                     (anEntry == nodeToRemovePtr->getItem());
      if (ableToDelete)
      {
         auto aftPtr = nodeToRemovePtr->getNext();
         if (nodeToRemovePtr == headPtr)
         {
            // Delete the first node in the chain
            headPtr = aftPtr;
         }
         else
         {
         
            // Disconnect indicated node from chain by connecting the
            // prior node with the one after
            prevPtr->setNext(aftPtr);
         }  // end if
         
         itemCount--;  // Decrease count of entries
      }  // end if
   }  // end if

   return ableToDelete;
}  // end removeSorted

template<class ItemType>
int LinkedSortedList<ItemType>::getPosition(const ItemType& anEntry) const
{
   int position = 1;
   auto curPtr = headPtr;
   
   while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) )
   {
      curPtr = curPtr->getNext();
      position++;
   } // end while
   
   if ( (curPtr == nullptr) || (anEntry != curPtr->getItem()) )
      position = -position;
   
   return position;
}  // end getPosition

//=====================
// List operations:

template<class ItemType>
bool LinkedSortedList<ItemType>::remove(int position)
{
   bool ableToDelete = (position >= 1) && (position <= itemCount);
   if (ableToDelete)
   {
      if (position == 1)
      {
         // Delete the first node in the chain
         headPtr = headPtr->getNext();
      }
      else
      {
         // Find node that is before the one to delete
         auto prevPtr = getNodeAt(position - 1);
         
         // Point to node to delete
         auto curPtr = prevPtr->getNext();
         
         // Disconnect indicated node from chain by connecting the
         // prior node with the one after
         prevPtr->setNext(curPtr->getNext());
      }  // end if
      
      itemCount--;  // Decrease count of entries
   }  // end if
   
   return ableToDelete;
}  // end remove

template<class ItemType>
void LinkedSortedList<ItemType>::clear()
{
   while (!isEmpty())
      remove(1);
}  // end clear

template<class ItemType>
ItemType LinkedSortedList<ItemType>::getEntry(int position) const
                                       throw(PrecondViolatedExcep)
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      auto nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else
   {
      std::string message = "getEntry() called with an empty list or ";
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message)); 
   }  // end if
}  // end getEntry

template<class ItemType>
bool LinkedSortedList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedSortedList<ItemType>::getLength() const
{
   return itemCount;
}  // end getLength

template<class ItemType>
auto LinkedSortedList<ItemType>::getNodeBefore(const ItemType& anEntry) const
{
   auto curPtr = headPtr;
   std::shared_ptr<Node<ItemType>> prevPtr; // Default constructor initializes to nullptr and refCount = 0
   
   while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) )
   {
      prevPtr = curPtr;
      curPtr = curPtr->getNext();
   } // end while
   
   return prevPtr;
} // end getNodeBefore

template<class ItemType>
auto LinkedSortedList<ItemType>::getNodeAt(int position) const
{
   assert( (position >= 1) && (position <= itemCount) );
   
   // Count from the beginning of the chain
   auto curPtr = headPtr;
   for (int skipNodePtr = 1; skipNodePtr < position; skipNodePtr++)
      curPtr = curPtr->getNext();
   
   return curPtr;
}  // end getNodeAt
//  End of implementation file.
