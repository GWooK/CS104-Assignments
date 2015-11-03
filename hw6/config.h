#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>

class Config{
private:
	
public:
	static std::map<std::string, std::string> map_;
	static void Init(char filename[]);
	static std::string Get(std::string key);
};
#endif