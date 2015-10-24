#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QRadioButton>
#include "myset.h"

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
	QRadioButton * singleRadio;
	QRadioButton * andRadio;
	QRadioButton * orRadio;

	/*Results ordering form*/
	QRadioButton * filenameRadio;
	QRadioButton * outgoingRadio;
	QRadioButton * incomingRadio;

	/*Results list*/
	QVBoxLayout * resultsLayout;
	QLabel * legendLabel;
	QListWidget * resultListWidget;


	/*Quit button*/


	/*Web page window */


	/*Data*/
	std::set<WebPage *> resultSet;
}