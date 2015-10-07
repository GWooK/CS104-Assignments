#include <iostream>
#include <set>
#include <vector>
#include <string>
#include "markdownparser.h"
#include "webpage.h"
#include "searcheng.h"

using namespace std;

void display_results(set<WebPage*>& results);

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "usage: ./search index_file...Please provide an index file" << endl;
    return 1;
  }

  //Initialize the search engine
  SearchEng engine;
  PageParser * mdParser = new MarkdownParser();
  engine.add_parse_from_index_file(argv[1], mdParser);


  string myline;
  bool done = false;
  while( !done ){
    cout << "\n++++++++++++++++++++" << endl;
    cout << "Enter search terms: " << endl;
    getline(cin, myline);
    cout << "++++++++++++++++++++\n" << endl;

    //Exit the application
    if(myline == "."){
      done = true;
    }

    if(myline == ""){
      continue;
    }

    set<WebPage *> results = engine.query(myline);
    display_results(results);
  }

  delete mdParser;
  return 0;
}

void display_results(set<WebPage*>& results)
{
  int hits = results.size();
  cout << hits << " hits." << endl;
  cout << "=====" << endl;
  int i=0;
  for(set<WebPage*>::iterator it = results.begin();
      it != results.end();
      ++it)
    {
      cout << (*it)->filename() << endl;
      cout << "+---+" << endl;
      cout << (**it) << "\n" << endl;
      i++;
    }
  
}
