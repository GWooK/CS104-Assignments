#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"

class SearchEng {
 public:
  SearchEng();
  ~SearchEng();
  void add_parse_from_index_file(std::string index_file, 
				 PageParser* parser);
  void add_parse_page(std::string filename, 
		      PageParser* parser);

  /**** Add other desired member functions here *****/
  WebPage * get_webpage(std::string filename);
  void add_to_wordmap(std::string word, std::string filename);
  MySet<WebPage *> word_query(std::string word);
  std::set<WebPage *> query(std::string entry);
 private:
 std::map<std::string, MySet<std::string>> wordToFilenamesSetMap;
 std::map<std::string, WebPage *> filenameToWebPageMap;
};

#endif
