#include <fstream>
#include <iostream>
#include "stackint.h"
#include <map>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

//Map
map<int, bool> variableMap;
const int OPEN_PAREN = -1;
const int CLOSE_PAREN = -2;
const int AND = -3;
const int OR = -4;
const int NEG = -5;
const int T = -6;
const int F = -7;

void initVariableMap(char * definputfilename){
	//The variable definition input
	ifstream definput(definputfilename);
	if(!definput.is_open()){
		cerr << "Unable to open the second input file!" << endl;
	}

	//Init variables
	string line;
	while(!definput.eof()){
		getline(definput, line);
		//cout << line;

		int key;
		char value;

		istringstream iss(line);

		iss >> key;
		iss >> value;

		//if value == T, val is true. otherwise, its false
		bool val = (value == 'T');

		variableMap.emplace(key, val);
	}
}

string evaluateExpression(string expression){
	StackInt stack;
	bool badFormatted = false;

	string buffer = "";

	string::size_type i = 0;
	char c;
	while(i < expression.size()){
		//pick a char
		c = expression[i];
		i++;

		//Push values to the stack
		if(isdigit(c)){
			buffer += c;
		} else if(buffer != ""){
			istringstream iss(buffer);
			int valN;
			iss >> valN;
			buffer = "";
			stack.push(valN);
		}

		switch(c){
			case 'T':
				stack.push(T);
				break;
			case 'F':
				stack.push(F);
				break;
			case '&':
				stack.push(AND);
				break;
			case '|':
				stack.push(OR);
				break;
			case '~':
				stack.push(NEG);
				break;
			case '(':
				stack.push(OPEN_PAREN);
				break;
		}

		//Parse a closed expression
		if(c == ')'){
			int foundValues = 0;
			bool foundOperator = false;
			int oper = 0;
			StackInt tempStack; //store all the variables and constants

			//Evaluate a subexpression
			while(!stack.empty()){
				int value = stack.top();
				stack.pop();
				
				//Check if its a constant
				if(value == T || value == F){
					if(foundOperator)
						foundOperator = false;

					tempStack.push(value);
					foundValues++;

					continue;
				}

				//Check if its a variable
				auto it = variableMap.find(value);
				if(it != variableMap.end()){
					if(foundOperator)
						foundOperator = false;

					tempStack.push(it->second?T:F);
					foundValues++;

					continue;
				} else {
					if (value >= 0){
						return "Unknown Variable";
					}

					//found a extra operator
					if (foundOperator){
						badFormatted = true;
						break;
					}
				}

				//Handle operators
				if(foundValues > 0){
					if(value == AND || value == OR){
						//A different operator was found!
						if(oper != 0 && oper != value){
							badFormatted = true;
							break;
						}


						if(value == AND){
							oper = AND;
							foundOperator = true;
						} else if (value == OR){
							oper = OR;
							foundOperator = true;
						}
					}
				}

				//Negative operator
				if(value == NEG){
					if(foundValues > 0){
						int tVal = tempStack.top();

						if(tVal == T || tVal == F){
							tempStack.pop();
							if(tVal == T){
								tempStack.push(F);
							} else {
								tempStack.push(T);
							}
						}
					}
				}


				//Check inconsistent parenthesis formation
				if(value == OPEN_PAREN && foundValues > 1){
					bool result;
					result = tempStack.top() == T;
					tempStack.pop();
					while(!tempStack.empty()){
						if(oper == AND){
							result = result && (tempStack.top() == T);
						}else{
							result = result || (tempStack.top() == T);
						}
						tempStack.pop();
					}

					stack.push(result?T:F);
					break;
				} 
			}
		}
	}

	if(badFormatted || stack.empty()){
		return "Malformed\t";
	}


	int value = stack.top();
	stack.pop();

	//Handle outside negations operators
	while(!stack.empty()){
		int ex = stack.top();
		stack.pop();
		if(ex != NEG){
			return "Malformed\t";
		}
		value = value == T?F:T;
	}

	if(stack.empty()){
		if(value == T){
			return "True\t";
		} else if (value == F){
			return "False\t";
		} else {
			return "Malformed\t";
		}
	} else {
		return "Malformed\t";
	}
}


int main(int argc, char *argv[]){
	//Check the arguments
	if(argc < 3){
		cerr << "You must pass by argument the input filenames!" << endl;
		return 0;
	}

	//The input
	ifstream input(argv[1]);
	if(!input.is_open()){
		cerr << "Unable to open input file!" << endl;
	}

	//Init the the variable map
	initVariableMap(argv[2]);

	//Read and evaluate expressions
	string line;
	while(!input.eof()){
		getline(input, line);
		line = evaluateExpression(line);
		cout << line << endl;
	}
}