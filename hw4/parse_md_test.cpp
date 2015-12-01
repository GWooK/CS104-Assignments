#include <iostream>
#include <fstream>
#include "util.h"
#include "myset.h"	

// Modify this to include student's implementation of md_parser 
#include "md_parser.h" 

// Change this to be the name of the class that the student has created for their MD Parser.
#define MD_PARSER MDParser

int main(int argc, char *argv[])
{
	if(argc < 3) { std::cout << "Program usage: ./parse_md_test file.in file.out"; }

	MySetString allWords, allLinks;
	MD_PARSER mdParser;
	mdParser.parse(argv[1], allWords, allLinks);

	std::ofstream outFile(argv[2]);
	if(outFile.fail())
	{
		std::cerr << "Error opening file " << argv[2] << ". Program aborting." << std::endl;
	}

	outFile << "All Words:" << std::endl;
	for(MySetString::iterator it = allWords.begin(); it != allWords.end(); ++it)
	{
		outFile << *it << std::endl;
	}

	outFile << "All Links:" << std::endl;
	for(MySetString::iterator it = allLinks.begin(); it != allLinks.end(); ++it)
	{
		outFile << *it << std::endl;
	}

	outFile.close();

	return 0;
}
