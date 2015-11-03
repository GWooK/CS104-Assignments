#include "webpage.h"
#include <QCoreApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QTextEdit>
#include <QLabel>
#include <vector>

class WebPageWindow : public QWidget{
	Q_OBJECT
public:
	WebPageWindow();
	~WebPageWindow();

	void updateWebPage(WebPage * page);
private slots:
	void updateLists();
	void selectIncomingLink(QListWidgetItem * item);
	void selectOutgoingLink(QListWidgetItem * item);
private:
	/*Top */
	QLabel * filenameLabel;

	/*Content */ 
	QTextEdit * contentText;

	/*Lists */
	QListWidget * incomingLinksList;
	QListWidget * outgoingLinksList;

	/*Results ordering form*/
	QButtonGroup * orderingButtonGroup;
	QRadioButton * filenameRadio;
	QRadioButton * outgoingRadio;
	QRadioButton * incomingRadio;

	/*Data*/
	WebPage * page;
	std::vector<WebPage *> outgoingList;
	std::vector<WebPage *> incomingList;
};