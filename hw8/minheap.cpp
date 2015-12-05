#include "minheap.h"
#include <exception>

MinHeap::MinHeap (int d){
	//items.push_back(std::make_pair(" ", 0));

	if(d < 2){
		throw std::exception();
	}

	this->d = d;

	count = 0;
}


MinHeap::~MinHeap (){

}

/* adds the item to the heap, with the given priority. */
void MinHeap::add (std::string item, int priority){
	auto pair = std::make_pair(item, priority);
	items.push_back(pair);
	
	count++;

	int loc = trickleUp(items.size()-1);

	auto priority_pair = std::make_pair(item, loc);	

	priorities.add(priority_pair);
}

 /* returns the element with smallest priority.  If
    multiple items have the smallest priority, it returns
    the string which comes first alphabetically.
    Throws an exception if the heap is empty. */
const std::string & MinHeap::peek () const{
	if(count <= 0)
		throw std::exception();

	return items[0].first;
}


/* removes the element with smallest priority.  If
    multiple items have the smallest priority, it removes
    the string which comes first alphabetically.
    Throws an exception if the heap is empty. */
void MinHeap::remove (){
	if(isEmpty())
		throw std::exception();

	items[0] = items.back();
	items.pop_back();
	count--;

	heapify(0);
}
 
 /* updates the priority for the specified element.
    You may want this function to do nothing if the new 
    priority is higher than the old one.
    Throws an exception if the item is not in the heap. */  
void MinHeap::update (std::string item, int priority){
	if(isEmpty())
		throw std::exception();

	try{
		int loc = priorities.find(item);
		items[loc].second = priority;
		loc = trickleUp(loc);

		priorities.update(items[loc]);

		heapify(0);
	} catch (std::exception e){
		throw e;
	}
}

 /* returns true iff there are no elements on the heap. */
bool MinHeap::isEmpty (){
	return count <= 0;
}

void MinHeap::swap(int i, int j){
	auto temp = items[i];
	items[i] = items[j];
	items[j] = temp;
}

/* return the parent of i */
int MinHeap::parent(int i){
	return (i - 1) / d;
}

/* return the kth child */
int MinHeap::kchild(int p, int k){
	if(k < 0 || k > d){
		return -1;
	}

	int child = d * p + k;
	
	return child <= count ? child : -1;
}

int MinHeap::trickleUp(int loc){
	int par = parent(loc);

	while(par >= 0){
		if(items[loc].second < items[par].second){
			swap(par, loc);
		} else if(items[loc].second == items[par].second && items[loc].first < items[par].first){
			swap(par, loc);
		} else{
			break;
		}
		
		loc = par;
		par = parent(loc);
	}

	return loc;
}

void MinHeap::heapify(int i){
	if(kchild(i, 0) == -1)
		return;

	//Smallest child
	int smaller = -1;
	for(int k = 0; k < d; k++){
		int child = kchild(i, k);
		if(child == -1)
			break;

		if(smaller == -1){
			smaller = child;
			continue;
		}

		if(items[child].second < items[smaller].second){
			smaller = child;
		} else if(items[child].second == items[smaller].second && items[child].first < items[smaller].first){
			smaller = child;
		} 
	}

	if(items[i].second > items[smaller].second){
		swap(smaller, i);
		heapify(smaller);
	} else if(items[i].second == items[smaller].second && items[i].first > items[smaller].first){
		swap(smaller, i);
		heapify(smaller);
	}
}