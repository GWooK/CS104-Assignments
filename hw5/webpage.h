#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <string>
#include <iostream>
#include "myset.h"

class WebPage
{
 public:
  WebPage();

  WebPage(std::string filename);

  ~WebPage();

  /**
   * Sets the filename/URL of this webpage
   */
  void filename(std::string fname) { filename_ = fname; }

  /**
   * Returns the filename/URL of this webpage
   */
  std::string filename() const {  return filename_; } ;

  /**
   * Updates the set containing all unique words in the text
   *  with the contents of the input parameter words
   */
  void all_words(const MySetString& words);

  /**
   * Returns all the unique, tokenized words in this webpage 
   */
  MySetString all_words() const { return all_words_;};

  /**
   * Adds a webpage that links to this page
   */
  void add_incoming_link(WebPage* wp);

  /**
   * Returns all webpages that link to this page
   */
  MySetWebPage incoming_links() const { return incoming_links_;} ;

  /**
   * Returns the number of incoming links
   */
  int number_of_incoming_links() { return incoming_links_.size();};

  /**
   * Adds a webpage that this page links to
   */
  void add_outgoing_link(WebPage* wp);

  /**
   * Returns all webpages this page links to
   */
  MySetWebPage outgoing_links() const { return outgoing_links_;};

  /**
   * Returns the number of outgoing links
   */
  int number_of_outgoing_links() { return outgoing_links_.size();};

  /**
   * Displays the webpage text to the screen 
   */
  friend std::ostream & operator<< (std::ostream & os, const WebPage & page);

  /**** Add other desired member functions here *****/

 private:
  /**** Add other desired data members here *****/
  MySetWebPage outgoing_links_;
  MySetWebPage incoming_links_;
  MySetString all_words_;
  std::string filename_;
  
};

class FilenameComp{
public:
  bool operator()(WebPage * lhs, WebPage * rhs){ return lhs->filename() < rhs->filename();}
};

class IncomingLinksComp{
public:
  bool operator()(WebPage * lhs, WebPage * rhs){return lhs->number_of_incoming_links() < rhs->number_of_incoming_links();}
};

class OutgoingLinksComp{
public:
  bool operator()(WebPage * lhs, WebPage * rhs){ return lhs->number_of_outgoing_links() < rhs->number_of_outgoing_links();}
};

#endif
