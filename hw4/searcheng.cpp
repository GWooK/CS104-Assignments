#include "searcheng.h"
#include <fstream>
#include "util.h"

SearchEng::SearchEng(){

}

SearchEng::~SearchEng(){
	auto iter = filenameToWebPageMap.begin();
	while(iter != filenameToWebPageMap.end()){
		delete iter->second;
		iter++;
	}
	filenameToWebPageMap.clear();
	wordToFilenamesSetMap.clear();
}

void SearchEng::add_parse_from_index_file(std::string index_file, 
			 PageParser* parser){
	std::ifstream input(index_file);

	for(std::string line; std::getline(input, line); ){
		if(line != ""){
			add_parse_page(line, parser);
		}
	}
}

void SearchEng::add_parse_page(std::string filename, 
	      PageParser* parser){
	//Declare the sets
	MySetString all_words;
	MySetString all_links;

	//Parse
	parser->parse(filename, all_words, all_links);

	//Update the webpage object
	WebPage * webpage = get_webpage(filename);
	webpage->all_words(all_words);
	for(std::string linkStr : all_links){
		WebPage * link = get_webpage(linkStr);
		webpage->add_outgoing_link(link);
		link->add_incoming_link(webpage);
	}

	//Update the word to filename map
	for(std::string word : all_words){
		add_to_wordmap(word, filename);
	}
}

//return the pointer for the webpage object associated with the filename
WebPage * SearchEng::get_webpage(std::string filename){
	auto iter = filenameToWebPageMap.find(filename);
	if(iter != filenameToWebPageMap.end()){
		return iter->second;
	} else {
		WebPage * webPage = new WebPage(filename);
		filenameToWebPageMap[filename] = webPage;
		return webPage;
	}
}

//Add a entry to the word to filename set
void SearchEng::add_to_wordmap(std::string word, std::string filename){
	//convert to lowercase
	word = convToLower(word);

	auto iter = wordToFilenamesSetMap.find(word);
	if(iter != wordToFilenamesSetMap.end()){
		iter->second.insert(filename);
	} else {
		MySetString set;
		set.insert(filename);
		wordToFilenamesSetMap[word] = set;
	}
}

//Process a one word query
MySetWebPage SearchEng::word_query(std::string word){
	word = convToLower(word);
	MySetWebPage set;

	auto iter = wordToFilenamesSetMap.find(word);
	if(iter != wordToFilenamesSetMap.end()){
		for(std::string filename : iter->second){
			set.insert(get_webpage(filename));
		}
	}

	return set;
}

//Process a query
std::set<WebPage *> SearchEng::query(std::string entry){
	//split the query input
	std::vector<std::string> entries = split(entry, ' ');
	
	//Select the operator
	char op = 'a';
	if(entries[0] == "AND"){
		op = '&';
	} else if(entries[0] == "OR"){
		op = '|';
	}

	//No operators and two or more words
	if(entries.size() > 1 && op == 'a'){
		//Thrown exception
	}

	//One word query
	if(op == 'a' && entries.size() == 1){
		return word_query(entries[0]);
	}

	//AND/OR query
	MySetWebPage set;
	for(unsigned int i = 1; i < entries.size(); i++){
		MySetWebPage localSet = word_query(entries[i]);
		if(op == '&'){
			set = set.set_intersection(localSet);
		} else if(op == '|') {
			set = set.set_union(localSet);
		}
	}
	return set;
}

