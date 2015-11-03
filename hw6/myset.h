#ifndef MYSET_H
#define MYSET_H

#include <set>
#include <string>

template<class T>
class MySet : public std::set<T>{
public:
  MySet();
  MySet<T> set_intersection(const MySet<T>& other);
  MySet<T> set_union(const MySet<T>& other);
};

template<class T>
MySet<T>::MySet() : std::set<T>() {
}

template<class T>
MySet<T> MySet<T>::set_intersection(const MySet<T>& other) {
	//Return set
	MySet<T> newSet;

	//Iterate
	typename MySet<T>::iterator it = this->begin();
	while(it != this->end()){
		if(other.count(*it) > 0){
			newSet.insert(*it);
		}
		it++;
	}

	it = other.begin();
	while(it != other.end()){
		if(this->count(*it) > 0){
			newSet.insert(*it);
		}
		it++;
	}


	return newSet;
}

template<class T>
MySet<T> MySet<T>::set_union(const MySet<T>& other) {
	//Return set
	MySet<T> newSet;

	//Iterate the first set
	typename MySet<T>::iterator it = this->begin();
	while(it != this->end()){
		newSet.insert(*it);
		it++;
	}

	//Iterate the second set
	it = other.begin();
	while(it != other.end()){
		newSet.insert(*it);
		it++;
	}

	return newSet;
}

#endif
