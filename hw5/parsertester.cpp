#include "markdownparser.h"
#include "iostream"

using namespace std;
int main(int argc, char *argv[])
{
	MySetString allWords;
	MySetString allLinks;

	if(argc < 2){
		cerr << "You must pass by argument the input and output filenames!" << endl;
		return 0;
	}

	string filename(argv[1]);

	MarkdownParser parser;

	parser.parse(filename, allWords, allLinks);

	cout << "| Words |" << endl;

	for(string word : allWords){
		cout << word << endl;
	}

	cout << "| Link |" << endl;
	for(string link : allLinks){
		cout << link << endl;
	}
}