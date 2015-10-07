#include "pageparser.h"

class MarkdownParser : public PageParser{
public:
	~MarkdownParser();
	MarkdownParser();

	void parse(std::string filename,
		     MySetString& allWords,
		     MySetString& allLinks) override;
private:

};