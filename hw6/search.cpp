#include <iostream>
#include "search_window.h"
#include <QApplication>
#include "config.h"

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "usage: ./search index_file...Please provide an index file" << endl;
    return 1;
  }

  //Initialize config file
  Config::Init(argv[1]);

  //QT stuff
  QApplication app(argc, argv);

  SearchWindow win;
  win.show();

  return app.exec();
}