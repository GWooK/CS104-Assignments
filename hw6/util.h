#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

std::string convToLower(std::string src);
std::vector<std::string> split(const std::string s, char c);
std::string intToString(int n);
std::string floatToString(float n);
int stringToInt(std::string s);
float stringToFloat(std::string s);

#endif
