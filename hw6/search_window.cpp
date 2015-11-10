#include "search_window.h"
#include "msort.h"
#include "QApplication"
#include "util.h"
#include "config.h"
#include "iostream"
#include "myset.h"

using namespace std;
SearchWindow::SearchWindow(){
	//Overall layout
	overallLayout = new QHBoxLayout();

	/*Results Layout*/
	resultsLayout = new QVBoxLayout();
	overallLayout->addLayout(resultsLayout);
	legendLabel = new QLabel("Filename\t#Incoming Links\t#Outgoing Links\tPagerank");
	resultsLayout->addWidget(legendLabel);
	resultListWidget = new QListWidget();
	connect(resultListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(displayWebpage(QListWidgetItem *)));
	resultsLayout->addWidget(resultListWidget);


	/*Search Layout*/
	searchLayout = new QVBoxLayout();
	searchInput = new QLineEdit();
	searchLayout->addWidget(searchInput);
	//Search criteria
	QHBoxLayout * criteriaLayout = new QHBoxLayout();
	searchButtonGroup = new QButtonGroup();
	singleRadio = new QRadioButton("Single");
	singleRadio->setChecked(true);
	andRadio= new QRadioButton("AND");
	orRadio = new QRadioButton("OR");
	criteriaLayout->addWidget(singleRadio);
	criteriaLayout->addWidget(andRadio);
	criteriaLayout->addWidget(orRadio);
	searchButtonGroup->addButton(singleRadio, 0);
	searchButtonGroup->addButton(andRadio, 1);
	searchButtonGroup->addButton(orRadio, 2);
	searchLayout->addLayout(criteriaLayout);
	//Search button
	searchButton = new QPushButton("Search");
	searchLayout->addWidget(searchButton);
	searchLayout->setAlignment(Qt::AlignTop);
	connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));

	//Ordering criteria
	QVBoxLayout * orderingLayout = new QVBoxLayout();
	legendLabel = new QLabel("\nOrder by:");
	orderingLayout->addWidget(legendLabel);
	QHBoxLayout * orderingRadioButtonsLayout = new QHBoxLayout();
	orderingButtonGroup = new QButtonGroup();
	pageRankRadio = new QRadioButton("Pagerank");
	pageRankRadio->setChecked(true);
	filenameRadio = new QRadioButton("Filename");
	outgoingRadio = new QRadioButton("#Outgoing Links");
	incomingRadio = new QRadioButton("#Incoming Links");

	orderingRadioButtonsLayout->addWidget(pageRankRadio);
	orderingRadioButtonsLayout->addWidget(filenameRadio);
	orderingRadioButtonsLayout->addWidget(incomingRadio);
	orderingRadioButtonsLayout->addWidget(outgoingRadio);
	orderingButtonGroup->addButton(filenameRadio, 0);
	orderingButtonGroup->addButton(incomingRadio, 1);
	orderingButtonGroup->addButton(outgoingRadio, 2);
	orderingButtonGroup->addButton(pageRankRadio, 3);
	connect(filenameRadio, SIGNAL(clicked()), this, SLOT(updateResultList()));
	connect(incomingRadio, SIGNAL(clicked()), this, SLOT(updateResultList()));
	connect(outgoingRadio, SIGNAL(clicked()), this, SLOT(updateResultList()));
	connect(pageRankRadio, SIGNAL(clicked()), this, SLOT(updateResultList()));
	orderingLayout->addLayout(orderingRadioButtonsLayout);
	
	//Layouting...
	QVBoxLayout * rightLayout = new QVBoxLayout();
	rightLayout->addLayout(searchLayout);
	resultsLayout->addLayout(orderingLayout);

	//Quit Button
	quitButton = new QPushButton("Quit");
	connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));
	rightLayout->addWidget(quitButton); 
	overallLayout->addLayout(rightLayout);

	//Set layout
	setLayout(overallLayout);

	//Create webpage window
	webpageWin = new WebPageWindow();

	/*SearchEngine stuff*/
	engine.add_parse_from_index_file(Config::Get("INDEX-FILE"), &mdParser);
}

SearchWindow::~SearchWindow(){

}

void SearchWindow::search(){
	if(searchInput->text().isEmpty()){
		return;
	}

	string query = searchInput->text().toStdString();

	//Check operator
	int op = searchButtonGroup->checkedId();
	bool queryIsInvalid = false;
	switch(op){
		case 0:
		queryIsInvalid = split(query, ' ').size() > 1;
		break;
		case 1:
		queryIsInvalid = split(query, ' ').size() < 2;
		query = "and " + query;
		break;
		case 2:
		queryIsInvalid = split(query, ' ').size() < 2;
		query = "or " + query;
		break;
	}

	if(queryIsInvalid){
		//Show error pop up!
		QWidget * popup = new QWidget();
		QHBoxLayout * popuplayout = new QHBoxLayout();
		QLabel * messageLabel = new QLabel("Invalid input!");
		popuplayout->addWidget(messageLabel);
		popup->setLayout(popuplayout);
		popup->show();
		return;
	}

	//Search and update the list
	MySet<WebPage *> resultSet = engine.query(query);
	engine.compute_pagerank(resultSet);
	resultList.clear();
	for(WebPage * page : resultSet){
		resultList.push_back(page);
	}

	//Sort and update the list of pages
	updateResultList();
}

void SearchWindow::quit(){
	QApplication::quit();
}

void SearchWindow::updateResultList(){
	//Sort the list
	sortResultList();

	//Clear the list
	while((int)resultListWidget->count() > 0){
		auto item = resultListWidget->takeItem(0);
		delete item;
	}

	//Update the list
	for(WebPage * page : resultList){
		string pageString = page->filename();
		pageString += "\tI: "+intToString(page->number_of_incoming_links());
		pageString += "\tO: "+intToString(page->number_of_outgoing_links());
		pageString += "\tR: "+floatToString(engine.get_pagerank(page));
		resultListWidget->addItem(QString::fromStdString(pageString));
	}
}

void SearchWindow::sortResultList(){
	//Check operator
	int op = orderingButtonGroup->checkedId();
	switch(op){
		case 0:
		FilenameComp compF;
		mergeSort(resultList, compF);
		break;
		case 1:
		IncomingLinksComp compI;
		mergeSort(resultList, compI);
		break;
		case 2:
		OutgoingLinksComp compO;
		mergeSort(resultList, compO);
		break;
		case 3:
		PagerankComp compRank(&engine);
		mergeSort(resultList, compRank);
		break;

	}
}

void SearchWindow::displayWebpage(QListWidgetItem *){
	unsigned int pageIndex = (unsigned int) resultListWidget->currentRow();

	if((int)pageIndex >= (int)resultList.size() || (int)pageIndex < 0)
		return;

	webpageWin->updateWebPage(resultList[pageIndex]);
	webpageWin->show();
}