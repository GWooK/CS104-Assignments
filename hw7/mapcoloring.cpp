#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "rbbst.h"

using namespace std;

/*Make it true to print debug messages*/
bool print = false;

//Input parser
void parseInput(char * filename, map<char, set<char>> & countries, vector<vector<char>> & grid){
	ifstream input(filename);
	if(!input.is_open()){

	}

	int nCountries; int nRows; int nColumns;
	input >> nCountries;
	input >> nRows;
	input >> nColumns;

	/*read the map*/
	//vector<vector<char>> grid;

	for(int i = 0; i < nRows; i++){
		vector<char> row;
		string s;
		input >> s;
		for(char c : s){
			row.push_back(c);
		}
		grid.push_back(row);
	}

	countries.clear();
	//Vertically
	for(int i = 0; i < nColumns; i++){
		char previous = grid[0][i];
		for(int j = 0; j < nRows; j++){
			char c = grid[j][i];
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
	if(print){
		cout << "Adjacency list" << endl;
		for(auto iter = countries.begin(); iter != countries.end(); iter++){
			cout << iter->first	<< " : ";
			auto set = iter->second;
			for(auto c : set){
				cout << c << " ";
			}
			cout << endl;
		}
	}
	
}

bool mapIsValid(char country, map<char, set<char>> & countries, RedBlackTree<char, int> & countriesColors){
	
	int color = countriesColors.find(country)->second;

	for(char adj : countries[country]){
		int adColor = countriesColors.find(adj)->second;
		if(color == adColor){
			return false;
		}
	}

	return true;
}

bool solveHelper(map<char, set<char>> & countries, RedBlackTree<char, int> & countriesColors, map<char, set<char>>::iterator iter){
	if(iter == countries.end()){
		return true;
	}

	char country = iter->first;
	//cout << country << endl;

	int i = 1;
	do{
		//cout << country << " n: " << i << endl;
		countriesColors.add(make_pair(country, i));
		if(mapIsValid(country, countries, countriesColors)){
			if(solveHelper(countries, countriesColors, ++iter))
			{
				return true;
			}
			else{
				countriesColors.add(make_pair(country, 0));
				iter--;
			}
		}
		i++;
	} while(i < 5);

	countriesColors.add(make_pair(country, 0));
	iter--;
	
	return false;
}

void solve(map<char, set<char>> & countries, RedBlackTree<char, int> &countriesColors){
	/*Initialize*/
	for(auto iter = countries.begin(); iter != countries.end(); iter++){
		//cout << iter->first << " n: " << 0 << endl;
		countriesColors.add(make_pair(iter->first, 0));
	}

	solveHelper(countries, countriesColors, countries.begin());
}

void printCountries(vector<vector<char>> & grid, map<char, set<char>> & countries,  RedBlackTree<char, int> & countriesColors){
	//Colors
	cout << "Colors" << endl;
	for(auto iter = countries.begin(); iter != countries.end(); iter++){
		cout << iter->first << " : " << countriesColors.find(iter->first)->second << endl;
	}


	//Print the grid
	for(auto row : grid){
		for(auto c : row){
			int color = countriesColors.find(c)->second;
			//Color the map :)
			switch(color){
				case 1: cout << "\x1b[31m"; break;
      			case 2: cout << "\x1b[34m"; break;
                case 3: cout << "\x1b[37m"; break;
                case 4: cout << "\x1b[32m"; break;
			}
			cout << c;
		}
		cout << endl;
	}

	cout << "\x1b[0m"; //restore the color
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
	vector<vector<char>> grid;

	parseInput(argv[1], countries, grid);

	solve(countries, countriesColors);

	if(print)
		printCountries(grid, countries, countriesColors);

	for(auto iter = countries.begin(); iter != countries.end(); iter++){
		cout << iter->first << " " << countriesColors.find(iter->first)->second << endl;
	}
}