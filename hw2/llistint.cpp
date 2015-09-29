#include "llistint.h"
#include <cstdlib>
#include <stdexcept>

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val)
{
	if(loc < 0 || loc > size())
		throw std::invalid_argument("bad location");

	Item * newItem = new Item();
	newItem->val = val;

	//The first element
	if(size() == 0)
	{
		head_ = newItem;
		head_->next = NULL;
		head_->prev = NULL;
		tail_ = head_;
		size_++;
		return;
	}

	//In the head
	if(loc == 0)
	{
		newItem->next = head_;
		newItem->prev = NULL;
		head_->prev = newItem;
		head_ = newItem;
		size_++;
		return;
	}

	//The the tail
	if(size() == loc)
	{
		newItem->next = NULL;
		newItem->prev = tail_;
		tail_->next = newItem;
		tail_ = newItem;
		size_++;
		return;
	}

	Item * temp = getNodeAt(loc);
	temp->prev->next = newItem;
	newItem->prev = temp->prev;
	newItem->next = temp;
	temp->prev = newItem;
	size_++;
}

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
	if(loc < 0 || loc >= size())
	{
		throw std::invalid_argument("bad location");
	}

	if(loc == 0)
	{
		head_->next->prev = NULL;
		Item * temp = head_;
		head_=head_->next;
		delete temp;
		size_--;
		return;
	}


	Item * item = getNodeAt(loc);
	item->prev->next = item->next;
	if(item->next)
		item->next->prev = item->prev;
	else
		tail_ = item->prev;
	size_--;
	delete item;
}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


/**
 * Complete the following function
 */
LListInt::Item* LListInt::getNodeAt(int loc) const
{
	Item * temp;

	temp = head_;
	for(int i = 0; i < loc; i++)
	{
		if(temp->next)
			temp = temp->next;
		else
		{
			temp = NULL;
			break;
		}
	}

	return temp;
}
