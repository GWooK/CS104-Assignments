#include <cctype>
#include <algorithm>
#include "util.h"
#include <sstream>
#include <iostream>

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

std::string intToString(int n){
	std::stringstream ss;
	ss << n;
	return ss.str();
}

std::string floatToString(float n){
  std::stringstream ss;
  ss << n;
  return ss.str();
}

int stringToInt(std::string s){
  return std::stoi(s);
}

float stringToFloat(std::string s){
  return std::stof(s);
}
