#include "search_window.h"

SearchWindow::SearchWindow(){
	//Overall layout
	overallLayout = new QHBoxLayout();

	//Results Layout
	resultsLayout = new QVBoxLayout();
	overallLayout->addLayout(resultsLayout);
	legendLabel = new QLabel("Filename\t#Incoming Links\t#Outgoing Links");
	resultsLayout->addWidget(legendLabel);
	resultListWidget = new QListWidget();
	resultsLayout->addWidget(resultListWidget);


	//Search Layout
	searchLayout = new QVBoxLayout();
	overallLayout.addLayout(searchLayout);
	searchInput = new QLineEdit();
	searchLayout->addWidget(searchInput);

}

SearchWindow::~SearchWindow(){

}