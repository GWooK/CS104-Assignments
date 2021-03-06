#include "searcheng.h"
#include <fstream>
#include "util.h"
#include "config.h"
#include <iostream>

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
	MySet<std::string> all_words;
	MySet<std::string> all_links;

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
		MySet<std::string> set;
		set.insert(filename);
		wordToFilenamesSetMap[word] = set;
	}
}

/* Given a candidate set, update the pagerank map */
void SearchEng::compute_pagerank(MySet<WebPage *> &candidateSet){
	int steps = stringToInt(Config::Get("STEP_NUMBER"));
	float e = stringToFloat(Config::Get("RESTART_PROBABILITY"));

	/*
	First iteration
	Initialize everyone with rank 1/n
	*/
	pagerankDataMap.clear();
	for(WebPage * page : candidateSet){
		PageRankData data;
		data.rank = 1.0f/candidateSet.size();
		data.page = page;

		page->add_incoming_link(page);
		page->add_outgoing_link(page);
		pagerankDataMap.emplace(page, data);
	}

	/*Next iterations*/
	for(int i = 1; i <= steps; i++){
		std::map<WebPage *, PageRankData> newData;
		for(WebPage * page : candidateSet){
			float sum = 0.0f;

			MySet<WebPage *> outSet = page->incoming_links().set_intersection(candidateSet);
			
			for(WebPage * outPage : outSet){
				MySet<WebPage *> outSet2 =  outPage->outgoing_links().set_intersection(candidateSet);
				sum += pagerankDataMap[outPage].rank/(float)outSet2.size();
				//std::cout << sum <<std::endl;
			}
			float val = (1.0-e)*sum + e*(1.0/candidateSet.size());
			//std::cout << val << std::endl;

			PageRankData data;
			data.rank = val;
			data.page = page;

			newData.emplace(page, data);
		}

		pagerankDataMap = newData;

		/*Debugging
		std::cout << "Iter - " << i << std::endl;
		for(WebPage * page : candidateSet){
			std::cout << page->filename() << " - " << newData[page].rank << std::endl;
		}*/
	}
}

float SearchEng::get_pagerank(WebPage * page){
	auto it = pagerankDataMap.find(page);
	if(it != pagerankDataMap.end()){
		return pagerankDataMap[page].rank;
	} 
	return 0.0f;
}

//Process a one word query
MySet<WebPage *> SearchEng::word_query(std::string word){
	word = convToLower(word);
	MySet<WebPage *> set;

	auto iter = wordToFilenamesSetMap.find(word);
	if(iter != wordToFilenamesSetMap.end()){
		for(std::string filename : iter->second){
			set.insert(get_webpage(filename));
		}
	}

	return set;
}

//Process a query
MySet<WebPage *> SearchEng::query(std::string entry){
	//split the query input
	std::vector<std::string> entries = split(entry, ' ');
	
	//Select the operator
	entries[0] = convToLower(entries[0]);
	char op = 'a';
	if(entries[0] == "and"){
		op = '&';
	} else if(entries[0] == "or"){
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
	MySet<WebPage *> set;
	for(unsigned int i = 1; i < entries.size(); i++){
		MySet<WebPage *> localSet = word_query(entries[i]);
		if(op == '&'){
			if(i == 1){
				set = localSet;
			}
			set = set.set_intersection(localSet);
		} else if(op == '|') {
			set = set.set_union(localSet);
		}
	}

	//Expanding set
	for(WebPage * page : set){
		set = set.set_union(page->incoming_links());
		set = set.set_union(page->outgoing_links());
	}
	return set;
}

