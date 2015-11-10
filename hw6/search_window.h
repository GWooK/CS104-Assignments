#include <QCoreApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include "myset.h"
#include <vector>
#include "markdownparser.h"
#include "webpage.h"
#include "searcheng.h"
#include "webpage_window.h"

class SearchWindow : public QWidget{
	Q_OBJECT
public:
	SearchWindow();
	~SearchWindow();
private slots:
	void search();
	void quit();
	void updateResultList();
	void sortResultList();
	void displayWebpage(QListWidgetItem *);
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
	QRadioButton * pageRankRadio;
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
	WebPageWindow * webpageWin;

	/*Search Engine */
	SearchEng engine;
	MarkdownParser mdParser;

	/*Data*/
	std::vector<WebPage *> resultList;
};