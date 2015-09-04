#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

void makePalindromesHelper(ostream& ofile, char* options, int size, string pal)
{

	string reversePal = string(pal.rbegin(), pal.rend());
	
	//Size of options
	string str(options);
	int optionsSize = str.size();

	//Base cases
	if(size == 0)
	{
		pal = pal + "" + reversePal;
		ofile << pal << endl;
	}
	else if(size == 1)
	{
		for(int i = 0; i < optionsSize; i++){
			string out = pal + options[i] + reversePal;
			ofile << out << endl;
		}
	}
	// xYx, where Y is palindrome and x is a character
	else if (size > 1)
	{
		for(int i = 0; i < optionsSize; i++){
			string out = pal + options[i];
			makePalindromesHelper(ofile, options, size-2, out);
		}
	}
}

void makePalindromes(ostream& ofile, char* options, int size)
{
	for(int i = 1; i <= size; i++)
	{
		makePalindromesHelper(ofile, options, i, "");
	}

}


int main(int argc, char* argv[])
{
  if(argc < 4){
    cerr << "Please provide an output file, a string of characters, and the max length" << endl;
    return 1;
  }

  ofstream ofile;
  ofile.open(argv[1]);
  int len = atoi(argv[3]);
  makePalindromes(ofile, argv[2], len);
  ofile.close();
  return 0;
}

