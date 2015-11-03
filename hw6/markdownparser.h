#include "pageparser.h"

class MarkdownParser : public PageParser{
public:
	~MarkdownParser();
	MarkdownParser();

	void parse(std::string filename,
		     MySet<std::string>& allWords,
		     MySet<std::string>& allLinks) override;
private:

};