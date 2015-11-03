#include "config.h"
#include "util.h"
#include <fstream>

std::map<std::string, std::string> Config::map_;

//Read the config file and initialize the map
void Config::Init(char filename[]){

	//std::cout << filename << std::endl;

	//Input
	std::ifstream input(filename);
	if(!input.is_open()){
		//Shit happens
		//Thrown Exception
		return;
	}

	//For each line
	for(std::string line; std::getline(input, line);){
		//Ignore comments
		auto values = split(line, '#');
		line = values[0];

		//parse
		std::string key = "";
		std::string value = "";
		bool mid = false;
		for(char c : line){
			//ignore whitespace
			if(c == ' '){
				continue;
			}

			//found the equal signal
			if(c == '='){
				mid = true;
				continue;
			}

			if(!mid)
				key += c;
			else
				value += c;
		}

		Config::map_.emplace(key, value);
		
	}
}

//Get a value
std::string Config::Get(std::string key){
	auto it = Config::map_.find(key);
	if(it == Config::map_.end()){
		return "";
	}

	return Config::map_[key];
}