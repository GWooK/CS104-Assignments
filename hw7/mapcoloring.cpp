#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "rbbst.h"

using namespace std;

//Input parser
void parseInput(char * filename, map<char, set<char>> & countries){
	ifstream input(filename);
	if(!input.is_open()){

	}

	int nCountries; int nRows; int nColumns;
	input >> nCountries;
	input >> nRows;
	input >> nColumns;

	/*read the map*/
	vector<vector<char>> grid;

	for(int i = 0; i < nRows; i++){
		vector<char> row;
		string s;
		input >> s;
		for(char c : s){
			row.push_back(c);
		}
		grid.push_back(row);
	}

	//Print the grid
	for(auto row : grid){
		for(auto c : row){
			cout << c;
		}
		cout << endl;
	}


	countries.clear();
	//Horizontally
	for(int i = 0; i < nRows; i++){
		auto row = grid[i];
		char previous = row[0];
		for(auto c: row){
			if(previous != c){
				countries[c].insert(previous);
				countries[previous].insert(c);
			}
			previous = c;
		}
	}

	//Vertically
	for(int i = 0; i < nRows; i++){
		char previous = grid[0][i];
		for(int j = 0; j < nColumns; j++){
			char c = grid[i][j];
			if(previous != c){
				countries[c].insert(previous);
				countries[previous].insert(c);
			}
			previous = c;
		}
	}


	/*Print the set and adjacencies */
	for(auto iter = countries.begin(); iter != countries.end(); iter++){
		cout << iter->first	<< " : ";
		auto set = iter->second;
		for(auto c : set){
			cout << c << " ";
		}
		cout << endl;
	}
}

bool mapIsValid(map<char, set<char>> & countries, RedBlackTree<char, int> countriesColors){
	for(auto iter = countries.begin(); iter != countries.end(); iter++){
		char country = iter->first;
		auto cIt = countriesColors.find(country);
		if(cIt != countriesColors.end()){
			int color1 = cIt->second;
			for(char adj : iter->second){ //Adjacency country
				auto aIt = countriesColors.find(adj);
				if(aIt != countriesColors.end()){
					int color2 = aIt->second;
					if(color1 != color2 && color2 != -1 && color1 != -1){
						return false;
					}
				}
			}
		}
	}

	return true;
}

void solve(map<char, set<char>> & countries, RedBlackTree<char, int> countriesColors){
	/*Initialize*/
	for(auto iter = countries.begin(); iter != countries.end(); iter++){
		countriesColors.add(make_pair(iter->first, -1));
	}

}

int main(int argc, char* argv[])
{
	if(argc < 2){
	   cerr << "Please provide an input file" << endl;
	   return 1;
	}

	//Countries vectors
	map<char, set<char>> countries;
	RedBlackTree<char,int> countriesColors;

	parseInput(argv[1], countries);

	solve(countries, countriesColors);
}