#include "markdownparser.h"
#include <stack>
#include <fstream>
#include <ctype.h>
#include <queue>
#include <fstream>

using namespace std;

MarkdownParser::MarkdownParser(){

}

MarkdownParser::~MarkdownParser(){
	
}

bool linkIsValid(std::string filename){
	//Input
	ifstream input(filename);

	//Test if the link is valid
	if(!input.is_open()){
		return false;
	}
	return true;
}

void parseLink(MySet<string>& allWords,
	MySet<string>& allLinks, ifstream & input){

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
		//Parse desc
		string outputBuffer;
		for(char c : desc){
			if(isalpha(c)){
				outputBuffer += c;
				continue;
			} else if(outputBuffer != ""){
				allWords.insert(outputBuffer);
				outputBuffer = "";
			}
		}

		if(outputBuffer != ""){
			allWords.insert(outputBuffer);
		}

		//Insert link
		if(link!="" && linkIsValid(link)){
			allLinks.insert(link);
		}
	} else {
		string outputBuffer;
		//If bad constructed, parse the content of the queue
		while(cQueue.size() > 0){
			c = cQueue.front();
			cQueue.pop();
			//is c a letter?
			if(isalpha(c)){
				outputBuffer += c;
				continue;
			} else if(outputBuffer != ""){
				allWords.insert(outputBuffer);
				outputBuffer = "";
			}
		}
	}
}

void MarkdownParser::parse(string filename,
	MySet<string>& allWords,
	MySet<string>& allLinks){

	//Input
	ifstream input(filename);
	if(!input.is_open()){
		//Shit happens
		//Thrown Exception
	}

	string outputBuffer;
	char c;
	while(input.get(c)){
		//is c a letter?
		if(isalpha(c)){
			outputBuffer += c;
			continue;
		} else if(outputBuffer != ""){
			allWords.insert(outputBuffer);
			outputBuffer = "";
		}

		if (c == '[') {
			parseLink(allWords, allLinks, input); 
		}
	}
}