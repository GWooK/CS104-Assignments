#include "hashtable.h"
#include <math.h>
#include <cctype>
#include <exception>
#include <iostream>

/* Constructor that builds a hash table with 31 indices. */
HashTable::HashTable (){
	size = 31;
	//data.resize(size);
	for(int i = 0; i < size; i++){
		std::list<std::pair<std::string, int>> list;
		data.push_back(list);
	}
}

HashTable::~HashTable (){

}

/* adds new_item to the hashtable.  
  Conflicts should be resolved via chaining.
  You may use the STL list to accomplish this. 
  Throws an exception if the key is already 
  in the hashtable.*/  
void HashTable::add (std::pair<std::string, int> new_item){
	try{
		find(new_item.first);
	} catch(std::exception & e){
		//Check if load factor will be greater than 1.0
		if((double)(count + 1)/(double)size > 1.0){
			resize();
		}

		//Insert
		int h = hash(new_item.first);
		data[h].push_front(new_item);

		count++;

		return;
	}

	throw std::exception(); 
}

/* returns the value with the associated key. 
  Throws an exception if the key is not in the
  hashtable. */
const int& HashTable::find(std::string key) const{
	int h = hash(key);

	for(auto iter = data[h].begin(); iter != data[h].end(); iter++){
		if(iter->first == key){
			return iter->second;
		}
	}

	//Throw exception
	throw std::exception();
}

bool HashTable::contains(std::string key) const{
	int h = hash(key);

	for(auto iter = data[h].begin(); iter != data[h].end(); iter++){
		if(iter->first == key){
			return true;
		}
	}

	//Throw exception
	throw std::exception();
}


std::list<std::pair<std::string, int>>::iterator HashTable::auxFind(std::string key){
	int h = hash(key);

	for(auto iter = data[h].begin(); iter != data[h].end(); iter++){
		if(iter->first == key){
			return iter;
		}
	}

	//Throw exception
	throw std::exception();
}


/* removes the element with the associated key. 
  Throws an exception if the key is not in the
  hashtable. */
void HashTable::remove (std::string key){
	int h = hash(key);
	try{
		auto iter = auxFind(key);
		data[h].remove(*iter);
		count--;
	} catch(std::exception & e){
		throw std::exception();
	}
}

/* finds the item with the associated key, 
  and updates its value accordingly. 
  Throws an exception if the key is not in the
  hashtable. */
void HashTable::update (std::pair<std::string, int> new_value){
	//int h = hash(new_value.first);
	try{
		auto iter = auxFind(new_value.first);
		iter->second = new_value.second;
	} catch(std::exception & e){
		throw std::exception();
	}
}

void HashTable::resize(){
	//print();

	//Create a new data set
	std::vector<std::list<std::pair<std::string, int>>> new_data;

	//Keep the old one
	auto old_data = data;

	data = new_data;
	size = 2 * size + 1;
	count = 0;

	for(int i = 0; i < size; i++){
		std::list<std::pair<std::string, int>> list;
		data.push_back(list);
	}


	//reinsert all the data
	for(auto & list : old_data){
		for(auto pair : list){
			add(pair);
		}
	}

	old_data.clear();

	//std::cout << "Resized!" << std::endl;
	//print();
}

int evalChar(char c){
	c = tolower(c);

	int out = (int)c - (int)'a'; 
	if(out > 25)
		out = out%25;
	else if(out < 0)
		out = (out * -1) % 25;

	return out; 
}

/*Calculate the hash function*/
int HashTable::hash(std::string key) const{
	long long tKey = 0;

	int i = 1;
	for(char c : key){
		long long t = pow(29, (int)key.size() - i) * evalChar(c);
		tKey += t;
	}

	return tKey % size;
}

void HashTable::print(){
	for(int i = 0; i < size; i++){
		std::cout << i << ": ";
		for(auto pair : data[i]){
			std::cout << pair.first << " | ";
		}
		std::cout << std::endl;
	}
}

//Operators
const int & HashTable::operator[](const std::string key ){ 
	return find(key); 
};