#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

//Helper function to parse links
string parseLink(ifstream & input, char c)
{
	string link;
	string desc;
	string buffer;
	bool descOk = false;
	bool linkOk = false;

	char c2;
	//Read the Description
	if(c == '[')
	{
		while(input.get(c2))
		{
			if(c2 == ']')
			{
				descOk = true;
				break;
			}
			desc += c2;
		}
		input.get(c2);
	}

	//Read the Link
	if(c == '(' || c2 == '('){
		while(input.get(c2))
		{
			if(c2 == ')'){
				linkOk = true;
				break;
			}
			link += c2;
		}
	} 
	

	if(linkOk && descOk)
	{
		buffer = "LINK ("+link + ","+desc+")";
	}
	else if(linkOk)
	{
		buffer = "LINK ("+link + ","+link+")";
	}
	//If link parsing fails, parse normally the description
	else if(descOk)
	{	
		for (string::iterator c3 = desc.begin(), end = desc.end(); c3 != end; ++c3){
			if(isalpha(*c3))
			{
				buffer += *c3;
			}
		}
	}

	return buffer;
}

int main(int argc, char *argv[])
{
	//Check the arguments
	if(argc < 3)
	{
		cerr << "You must pass by argument the input and output filenames!" << endl;
		return 0;
	}

	//The input
	ifstream input(argv[1]);
	if(!input.is_open())
	{
		cerr << "Unable to open input file!" << endl;
	}

	//The output file
	//Declare the ofstream
	ofstream output;
	output.open(argv[2]);

	//Check if the file could be open
	if(output.fail())
		cerr << "Could not open the output file!";

	//Parsing
	string outputBuffer;
	string linkBuffer;

	char c;
	while(input.get(c))
	{
		//is c a letter?
		if(isalpha(c))
		{
			outputBuffer += c;
			continue;
		}
		else if(c == '[' || c == '(')
		{
			outputBuffer = parseLink(input, c);
		}

		if(outputBuffer != "")
		{
			output << outputBuffer << endl;
			cout << outputBuffer << endl;
			outputBuffer = "";
		}
	}


	input.close();
	output.close();
}


