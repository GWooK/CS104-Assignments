#include "llistint.h"
#include <iostream>

using namespace std;

int main()
{
  LListInt * list = new LListInt();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  list->insert(0, 3);

  // Check if the list is still empty.
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3) {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }


  // Insert an item.
  list->insert(1, 10);
  if (list->size() == 2) {
    cout << "SUCCESS: List has size 2 after two insertions." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after two insertions.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(1) == 10) {
    cout << "SUCCESS: 10 is at the 1st index of the list." << endl;
  } else {
    cout << "FAIL: 10 is not at the 1st index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // Insert an item at the head.
  list->insert(0, 5);
  //Check if the value is correct.
  if (list->get(0) == 5) {
    cout << "SUCCESS: 5 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 5 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }


  // Insert an item at the tail.
  list->insert(list->size(), 10);
  if (list->size() == 4) {
    cout << "SUCCESS: List has size 4 after four insertions." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after four insertions.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(list->size()-1) == 10) {
    cout << "SUCCESS: 10 is at the last index of the list." << endl;
  } else {
    cout << "FAIL: 10 is not at the last index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }


  //Insert 4 items
  list->insert(0,7);
  list->insert(2,8);
  list->insert(3,12);
  list->insert(list->size(),18);

  //Check the size
  if(list->size()==8)
  {
    cout << "SUCCESS: The size of the list is 8" << endl;
  }else
  {
    cout << "FAIL: 8 is not the size of the list, " << list->size() << "is instead;" << endl;
  }


  //Removing a item from a common node
  list->remove(5);
  if(list->size()==7)
  {
    cout << "SUCCESS: One item was removed" << endl;
  }else
  {
    cout << "FAIL: one item was not removed, " << list->size() << "is the size of the list;" << endl;
  }


  //Removing a item from the head
  list->remove(0);
  if(list->size()==6)
  {
    cout << "SUCCESS: One item was removed at the head" << endl;
  }else
  {
    cout << "FAIL: one item was not removed at the head, " << list->size() << "is the size of the list;" << endl;
  }

  //Removing a item from the tail
  list->remove(list->size()-6);
  if(list->size()==5)
  {
    cout << "SUCCESS: One item was removed at the tail" << endl;
  }else
  {
    cout << "FAIL: one item was not removed at the tail, " << list->size() << "is the size of the list;" << endl;
  }

  

  // Clean up memory.
  delete list;
}