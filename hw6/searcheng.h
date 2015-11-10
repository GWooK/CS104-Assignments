#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"

struct PageRankData{
  float rank;
  WebPage * page;
};


class SearchEng {
 public:
  SearchEng();
  ~SearchEng();
  void add_parse_from_index_file(std::string index_file, 
				 PageParser* parser);
  void add_parse_page(std::string filename, 
		      PageParser* parser);

  void compute_pagerank(MySet<WebPage *> &candidateSet);
  float get_pagerank(WebPage * page);

  /**** Add other desired member functions here *****/
  WebPage * get_webpage(std::string filename);
  void add_to_wordmap(std::string word, std::string filename);
  MySet<WebPage *> word_query(std::string word);
  MySet<WebPage *> query(std::string entry);
 private:
 std::map<std::string, MySet<std::string>> wordToFilenamesSetMap;
 std::map<std::string, WebPage *> filenameToWebPageMap;

 std::map<WebPage *, PageRankData> pagerankDataMap;
};

/*Pagerank comparator */
class PagerankComp{
public:
  SearchEng * engine;
  PagerankComp(SearchEng * eng) { engine = eng; };
  bool operator()(WebPage * lhs, WebPage * rhs){ return engine->get_pagerank(lhs) > engine->get_pagerank(rhs);}
};


#endif
