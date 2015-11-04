#include "config.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <set>

using namespace std;

//Enable to see debugging messages
bool debug = false;

/*Auxiliar parsing functions */
string parseLink(ifstream & input){

	//A copy of the stream
	string desc = "";
	string link = "";
	bool descIsOk = false;
	bool linkIsOk = false;
	queue<char> cQueue;

	char c;

	//Desc
	while(input.get(c)){
		cQueue.push(c);

		if(c == ']')
		{
			descIsOk = true;
			break;
		}
		desc += c;
	}

	//Link
	if(input.get(c))
		cQueue.push(c);
	if(c == '('){
		while(input.get(c))
		{
			cQueue.push(c);
			if(c == ')'){
				linkIsOk = true;
				break;
			}

			//If the link has a whitespace, it's invalid
			if(c == ' '){
				break;
			}
			link += c;
		}
	}

	if(descIsOk && linkIsOk){
		//Insert link
		if(link!=""){
			return link;
		}
	}

	return "";
}

int main(int argc, char* argv[])
{
	if(argc < 2){
	cerr << "usage: ./search index_file...Please provide an index file" << endl;
	return 1;
	}

	//Initialize config file
	Config::Init(argv[1]);

	//Auxiliar data structures
	set<string> discovered;
	vector<string> outputBuffer;
	stack<string> s;

	//Seed file initialize
	ifstream seed(Config::Get("INDEX-FILE"));
	if(!seed.is_open()){
		cerr << "Invalid seed file!" << endl;
	}

	//Crawling loop
	for(std::string line; std::getline(seed, line);){
		s.push(line);

		if(debug)
			cout << "reading " << line << endl;

		while(!s.empty()){
			string filename = s.top();
			s.pop();

			//Input
			ifstream input(filename);

			//Test if the link is valid
			if(!input.is_open()){
				continue;
			}

			//If the link was discovered earlier
			if(discovered.count(filename) > 0){
				continue;
			}

			//Parse and search links
			char c;
			discovered.insert(filename);
			outputBuffer.push_back(filename);

			if(debug)
				cout << "reading link " << filename << endl;

			while(input.get(c)){
				//is c a letter?
				if(isalpha(c)){
					continue;
				} 
				//link parser
				if (c == '[') {
					string link = parseLink(input);
					if(link == "")
						continue;
					s.push(link);
				}
			}
		}
	}

	//Outputting
	ofstream output;
	output.open(Config::Get("OUTPUT-FILE"));
	if(output.is_open()){
		for(string link : outputBuffer){
			if(debug)
				cout << link << endl;
			output << link << endl;
		}
		output.close();
	} else {
		cerr << "Can not write output file!" << endl;
	}
}