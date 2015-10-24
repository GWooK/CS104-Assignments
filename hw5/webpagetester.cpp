#include "webpage.h"
#include <string>
#include <iostream>

using namespace std;
int main(int argc, char *argv[]){
	if(argc < 2){
		cerr << "You must pass by argument the input and output filenames!" << endl;
		return 0;
	}

	string filename(argv[1]);

	WebPage test(filename);

	cout << test << endl;
}