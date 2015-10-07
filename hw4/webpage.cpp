#include "webpage.h"
#include "markdownparser.h"
#include "myset.h"
#include <fstream>
#include <queue>

WebPage::WebPage(){

}

WebPage::WebPage(std::string filename){
	this->filename(filename);
}

WebPage::~WebPage(){
	
}

void WebPage::all_words(const MySetString& words){
	all_words_ = words;
}

void WebPage::add_incoming_link(WebPage* wp){
	incoming_links_.insert(wp);
}

void WebPage::add_outgoing_link(WebPage* wp){
	outgoing_links_.insert(wp);
}

//Read a link substring
// If the link is valid return: "[description]"
//  otherwise, return the full readed content
std::string readLink(std::ifstream & input){
	//desc stores the full description text
	std::string desc = "";

	//Flag values
	bool descIsOk = false;
	bool linkIsOk = false;

	//A queue that store all readed characters
	std::queue<char> cQueue;

	//Description
	char c;
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
			if(c == ' '){
				break;
			}
		}
	}

	//Return statements
	if(descIsOk && linkIsOk){
		return "["+desc+"]";
	} else {
		std::string outputBuffer = "";
		//If bad constructed, return the content of the queue
		while(cQueue.size() > 0){
			c = cQueue.front();
			cQueue.pop();
			outputBuffer += c;
		}
		return outputBuffer;
	}
}

std::ostream & operator<< (std::ostream & os, const WebPage & page){
	//Input
	std::ifstream input(page.filename());
	if(!input.is_open()){
		//Shit happens
		//Thrown Exception
	}

	std::string outputBuffer = "";

	char c;
	while(input.get(c)){
		if(c == '['){
			outputBuffer += readLink(input);
		} else {
			outputBuffer += c;
		}
	}
	os << outputBuffer;
	input.close();
	return os;
}
