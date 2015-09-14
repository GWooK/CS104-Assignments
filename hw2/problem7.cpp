#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <set>
#include <utility>

using namespace std;

//Return the lowercased string
string toLower(string s)
{
	for(unsigned int i = 0; i < s.length(); ++i) {
    	s[i] = tolower(s[i]);
	}

	return s;
}

int main(int argc, char *argv[])
{
	//Check the arguments
	if(argc < 2)
	{
		cerr << "You must pass by argument the input filename!" << endl;
		return 0;
	}

	//The input
	ifstream input(argv[1]);
	if(!input.is_open())
	{
		cerr << "Unable to open input file!" << endl;
	}

	//Populating the set
	std::set<std::string> s;
	string wordBuffer;
	char c;
	while(input.get(c))
	{
		//is c a letter?
		if(isalpha(c))
		{
			wordBuffer += c;
		}
		else if(wordBuffer != "")
		{
			s.insert(toLower(wordBuffer));
			wordBuffer = "";

		}
	}

	//Prompt the user
	string entry = "";
	do
	{
		cout << "Please, insert one word:" << endl;
		getline(cin, entry);
		if(!entry.empty())
		{
			entry = toLower(entry);
			if(s.count(entry) > 0)
			{
				cout << "in the file!" << endl;
			}
			else
			{
				cout << "not in the file!" << endl;
			}
		}
	}while(entry != "");

	return 0;
}