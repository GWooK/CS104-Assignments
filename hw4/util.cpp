#include <cctype>
#include <algorithm>
#include "util.h"
#include <sstream>

std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

std::vector<std::string> split(const std::string s, char delimiter) {
   	std::vector<std::string> v;
   	std::stringstream ss(s);
   	std::string line;

  	while(getline(ss, line, delimiter)){
   		v.push_back(line);
   	}

   	return v;
}

