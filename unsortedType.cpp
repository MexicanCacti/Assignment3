/***************************************************************************************
*    Title: C++ Plus Data Structures SIXTH EDITION
*    Author: Nell Dale, Chip Weems
*    Date: 09/14/2023
*    Code version: C++11
*    Availability: Chapter 3
*
***************************************************************************************/

#include <iostream>
#include "unsortedType.h"

UnsortedType::UnsortedType() {
  length = 0;
  listData = NULL;
  currPos = NULL;
}

UnsortedType::~UnsortedType() {
  Node* temp = listData;
  
  while (listData != NULL) {        // go through each element in list, deallocate memory
    temp = listData;
    listData = listData->next;
    delete temp;
  }
}

void UnsortedType::MakeEmpty() {
  Node* temp;
  while (listData != NULL) {        // go through each element in list, deallocate memory
    temp = listData;
    listData = listData->next;
    delete temp;
  }
  length = 0;
}

bool UnsortedType::IsFull() const {
  try {                             // attempt to create node -> return false if can, catch bad_alloc if full -> return true
    Node* temp = new Node();   
    delete temp;
    return false;
  }
  catch (std::bad_alloc exception) {
    return true;
  }
}

int UnsortedType::GetLength() const {
  return length;  
}

ItemType UnsortedType::GetItem(ItemType& item, bool& found) {  
  Node* temp = listData;
  
  while (temp != NULL) {                                      // goes through every node in linked list and compares item to what we want. 
    if (temp->item.ComparedTo(item) == EQUAL) {
      found = true;                                           // found item, found = true, return the item
      return temp->item;
    }
    temp = temp->next;
  }
  found = false;                                              // didn't find item, found = false, return item tried to search for
  return item;
}

void UnsortedType::PutItem(ItemType item) {
  try {                                   // insert new node at front of list
    Node* NodeItem = new Node();
    NodeItem->item = item;
    NodeItem->next = listData;
    listData = NodeItem;
    length++;
  }
  catch (std::bad_alloc exception) {

  }

}

void UnsortedType::DeleteItem(ItemType item) {
  Node* temp = listData;
  
  if (temp->item.ComparedTo(item) == EQUAL) {     // check if first item in linked list is what we are looking for, if it is need to set head node to be the next node in list
    listData = listData->next;
    delete temp;
    length--;
    return;
  }
  
  Node* prev = temp;
  
  while (temp != NULL) {
    if (temp->item.ComparedTo(item) == EQUAL) {
      
      
      prev->next = temp->next;
      delete temp;
      length--;
      return;
    }
    prev = temp;
    temp = temp->next;
  }
}

void UnsortedType::ResetList() {
  currPos = NULL;
}
// Function: Initializes current position for an iteration through the list.
// Pre:  List has been initialized.
// Post: Current position is prior to list.

ItemType UnsortedType::GetNextItem() {
  if (currPos == NULL) {            // currPos is first element in list
    currPos = listData;
  }
  else if (currPos->next == NULL) { // currPos is last element in list
    return currPos->item;
  }
  else {
    currPos = currPos->next;
  }
  return currPos->item;
}
// Function: Gets the next element in list.
// Pre:  List has been initialized and has not been changed since last call.
//       Current position is defined.
//       Element at current position is not last in list.
//	     
// Post: Current position is updated to next position.
//       item is