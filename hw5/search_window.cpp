#include "search_window.h"

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
	andRadio= new QRadioButton("AND");
	orRadio = new QRadioButton("OR");
	criteriaLayout->addWidget(singleRadio);
	criteriaLayout->addWidget(andRadio);
	criteriaLayout->addWidget(orRadio);
	searchButtonGroup->addButton(singleRadio);
	searchButtonGroup->addButton(andRadio);
	searchButtonGroup->addButton(orRadio);
	searchLayout->addLayout(criteriaLayout);
	//Search button
	searchButton = new QPushButton("Search");
	searchLayout->addWidget(searchButton);
	searchLayout->setAlignment(Qt::AlignTop);

	//Ordering criteria
	QVBoxLayout * orderingLayout = new QVBoxLayout();
	legendLabel = new QLabel("\nOrder by:");
	orderingLayout->addWidget(legendLabel);
	QHBoxLayout * orderingRadioButtonsLayout = new QHBoxLayout();
	orderingButtonGroup = new QButtonGroup();
	filenameRadio = new QRadioButton("Filename");
	outgoingRadio = new QRadioButton("#Incoming Links");
	incomingRadio = new QRadioButton("#Outgoing Links");

	orderingRadioButtonsLayout->addWidget(filenameRadio);
	orderingRadioButtonsLayout->addWidget(incomingRadio);
	orderingRadioButtonsLayout->addWidget(outgoingRadio);
	orderingButtonGroup->addButton(filenameRadio);
	orderingButtonGroup->addButton(incomingRadio);
	orderingButtonGroup->addButton(outgoingRadio);
	orderingLayout->addLayout(orderingRadioButtonsLayout);
	
	//Layouting...
	QVBoxLayout * rightLayout = new QVBoxLayout();
	rightLayout->addLayout(searchLayout);
	resultsLayout->addLayout(orderingLayout);

	//Quit Button
	quitButton = new QPushButton("Quit");
	rightLayout->addWidget(quitButton); 

	overallLayout->addLayout(rightLayout);

	//Set
	setLayout(overallLayout);
}

SearchWindow::~SearchWindow(){

}