#include <iostream>
#include "search_window.h"
#include <QApplication>

using namespace std;

//void display_results(set<WebPage*>& results);

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "usage: ./search index_file...Please provide an index file" << endl;
    return 1;
  }

  //engine.add_parse_from_index_file(argv[1], mdParser);

  //QT stuff
  QApplication app(argc, argv);

  SearchWindow win;
  win.show();

  return app.exec();
}

/*
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
  
}*/
