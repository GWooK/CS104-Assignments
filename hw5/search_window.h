#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include "myset.h"
#include "markdownparser.h"
#include "webpage.h"
#include "searcheng.h"

class SearchWindow : public QWidget{
	Q_OBJECT
public:
	SearchWindow();
	~SearchWindow();
private:
	QHBoxLayout * overallLayout;

	/*Search form*/
	QVBoxLayout * searchLayout;
	QLineEdit * searchInput;
	QButtonGroup * searchButtonGroup;
	QRadioButton * singleRadio;
	QRadioButton * andRadio;
	QRadioButton * orRadio;

	QPushButton * searchButton;

	/*Results ordering form*/
	QButtonGroup * orderingButtonGroup;
	QRadioButton * filenameRadio;
	QRadioButton * outgoingRadio;
	QRadioButton * incomingRadio;

	/*Results list*/
	QVBoxLayout * resultsLayout;
	QLabel * legendLabel;
	QListWidget * resultListWidget;


	/*Quit button*/
	QPushButton * quitButton;

	/*Web page window */

	/*Search Engine */
	SearchEngine engine;
	MarkdownParser mdParser;

	/*Data*/
	std::set<WebPage *> resultSet;
};