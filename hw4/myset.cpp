#include "myset.h"
#include "webpage.h"

MySetString::MySetString() : std::set<std::string>() {
}

MySetString MySetString::set_intersection(const MySetString& other) {
	//Return set
	MySetString newSet;

	//Iterate
	MySetString::iterator it = begin();
	while(it != end()){
		if(other.count(*it) > 0){
			newSet.insert(*it);
		}
		it++;
	}

	it = other.begin();
	while(it != other.end()){
		if(count(*it) > 0){
			newSet.insert(*it);
		}
		it++;
	}


	return newSet;
}

MySetString MySetString::set_union(const MySetString& other) {
	//Return set
	MySetString newSet;

	//Iterate the first set
	MySetString::iterator it = begin();
	while(it != end()){
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

MySetWebPage::MySetWebPage() : std::set<WebPage*>() {}

MySetWebPage MySetWebPage::set_intersection(const MySetWebPage& other) {
	//Return set
	MySetWebPage newSet;

	//Iterate
	MySetWebPage::iterator it = begin();
	while(it != end()){
		if(other.count(*it) > 0){
			newSet.insert(*it);
		}
		it++;
	}

	it = other.begin();
	while(it != other.end()){
		if(other.count(*it) > 0){
			newSet.insert(*it);
		}
		it++;
	}

	return newSet;
}

MySetWebPage MySetWebPage::set_union(const MySetWebPage& other) {
	//Return set
	MySetWebPage newSet;

	//Iterate the first set
	MySetWebPage::iterator it = begin();
	while(it != end()){
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
