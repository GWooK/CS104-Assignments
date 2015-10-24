#include "msort.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct IntComp{
	bool operator()(const int & lhs, const int & rhs)
	{ // Uses string's built in operator< 
	  // to do lexicographic (alphabetical) comparison
	  return lhs < rhs; 
	}
};

struct AlphaStrComp {
	bool operator()(const string& lhs, const string& rhs) 
	{ // Uses string's built in operator< 
	  // to do lexicographic (alphabetical) comparison
	  return lhs < rhs; 
	}
};

struct LengthStrComp {
	bool operator()(const string& lhs, const string& rhs) 
	{ // Uses string's built in operator< 
	  // to do lexicographic (alphabetical) comparison
	  return lhs.size() < rhs.size(); 
	}
};

int main(){
	vector<int> vec;

	cout << "Type a lot of ints! (and stop typping '-1')" << endl;

	while(true){
		int in;
		cin >> in;

		if(in == -1){
			break;
		}

		vec.push_back(in);
	}

	/*
	cout << "Type 1 for AlphaComp or 2 for LenghComp" << endl;
	bool c;
	while(true){
		string in;
		cin >> in;
		if(in == "1"){
			c == true;
			break;
		}
		if(in == "2"){
			c == false;
			break;
		}
	}

	//Sort
	if(c){
		AlphaStrComp comp;
		mergeSort(vec, comp);
	} else {
		LengthStrComp comp;
		mergeSort(vec, comp);
	} */

	IntComp comp;
	mergeSort(vec, comp);

	//print the vector
	for(int i : vec){
		cout << i << endl;
	}
}