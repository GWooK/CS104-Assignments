#include "search_window.h"
#include "msort.h"
#include "QApplication"
#include "util.h"

using namespace std;
SearchWindow::SearchWindow(){
	//Overall layout
	overallLayout = new QHBoxLayout();

	/*Results Layout*/
	resultsLayout = new QVBoxLayout();
	overallLayout->addLayout(resultsLayout);
	legendLabel = new QLabel("Filename\t#Incoming Links\t#Outgoing Links");
	resultsLayout->addWidget(legendLabel);
	resultListWidget = new QListWidget();
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
	filenameRadio = new QRadioButton("Filename");
	filenameRadio->setChecked(true);
	outgoingRadio = new QRadioButton("#Incoming Links");
	incomingRadio = new QRadioButton("#Outgoing Links");

	orderingRadioButtonsLayout->addWidget(filenameRadio);
	orderingRadioButtonsLayout->addWidget(incomingRadio);
	orderingRadioButtonsLayout->addWidget(outgoingRadio);
	orderingButtonGroup->addButton(filenameRadio, 0);
	orderingButtonGroup->addButton(incomingRadio, 1);
	orderingButtonGroup->addButton(outgoingRadio, 2);
	connect(filenameRadio, SIGNAL(clicked()), this, SLOT(updateResultList()));
	connect(incomingRadio, SIGNAL(clicked()), this, SLOT(updateResultList()));
	connect(outgoingRadio, SIGNAL(clicked()), this, SLOT(updateResultList()));
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


	/*SearchEngine stuff*/
	engine.add_parse_from_index_file(QCoreApplication::arguments().at(1).toStdString(), &mdParser);
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
	switch(op){
		case 0:

		break;
		case 1:
		query = "AND " + query;
		break;
		case 2:
		query = "OR " + query;
		break;
	}

	//Search and update the list
	set<WebPage *> resultSet = engine.query(query);
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
	while(resultListWidget->count() > 0){
		auto item = resultListWidget->takeItem(0);
		delete item;
	}

	//Update the list
	for(WebPage * page : resultList){
		string pageString = page->filename();
		pageString += "\t"+intToString(page->number_of_incoming_links());
		pageString += "\t"+intToString(page->number_of_outgoing_links());
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
	}
}