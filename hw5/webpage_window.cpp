#include "webpage_window.h"
#include <sstream>
#include "msort.h"
#include "myset.h"
#include <iostream>

WebPageWindow::WebPageWindow(){
	QVBoxLayout *  overallLayout = new QVBoxLayout();

	/*Filename Label */
	filenameLabel = new QLabel();
	overallLayout->addWidget(filenameLabel);

	QHBoxLayout * midLayout = new QHBoxLayout();
	overallLayout->addLayout(midLayout);

	/*Content */
	contentText = new QTextEdit();
	contentText->setReadOnly(true);
	midLayout->addWidget(contentText);

	/*Incoming Links*/
	QVBoxLayout * incomingLayout = new QVBoxLayout();
	QLabel * incomingLabel = new QLabel("Incoming Links");
	incomingLinksList = new QListWidget();
	connect(incomingLinksList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(selectIncomingLink(QListWidgetItem *)));
	incomingLayout->addWidget(incomingLabel);
	incomingLayout->addWidget(incomingLinksList);
	midLayout->addLayout(incomingLayout);

	/*Outgoing Links*/
	QVBoxLayout * outgoingLayout = new QVBoxLayout();
	QLabel * outgoingLabel = new QLabel("Outgoing Links");
	outgoingLinksList = new QListWidget();
	connect(outgoingLinksList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(selectOutgoingLink(QListWidgetItem *)));
	outgoingLayout->addWidget(outgoingLabel);
	outgoingLayout->addWidget(outgoingLinksList);
	midLayout->addLayout(outgoingLayout);

	QHBoxLayout * bottomLayout = new QHBoxLayout();
	overallLayout->addLayout(bottomLayout);

	/*Ordering form*/
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
	connect(filenameRadio, SIGNAL(clicked()), this, SLOT(updateLists()));
	connect(incomingRadio, SIGNAL(clicked()), this, SLOT(updateLists()));
	connect(outgoingRadio, SIGNAL(clicked()), this, SLOT(updateLists()));
	bottomLayout->addLayout(orderingRadioButtonsLayout);

	setLayout(overallLayout);
}

WebPageWindow::~WebPageWindow(){
	
}

void WebPageWindow::updateWebPage(WebPage * webpage){
	if(webpage == nullptr)
		return;

	page = webpage;

	std::cout << page->filename() << std::endl;

	//Filename
	filenameLabel->setText(QString::fromStdString(page->filename()));

	//Content
	std::stringstream ss;
	ss << (*page);
	std::string content = ss.str();
	contentText->setText(QString::fromStdString(content));

	//Update lists
	updateLists();
}

void WebPageWindow::updateLists(){
	if(page == nullptr)
		return;
	//Populate the vectors
	incomingList.clear();
	auto incomingSet = page->incoming_links();
	for(WebPage * page : incomingSet){
		incomingList.push_back(page);
	}
	outgoingList.clear();
	auto outgoingSet = page->outgoing_links();
	for(WebPage * page : outgoingSet){
		outgoingList.push_back(page);
	}

	/* Sort? */
	int op = orderingButtonGroup->checkedId();
	switch(op){
		case 0:
		FilenameComp compF;
		mergeSort(incomingList, compF);
		mergeSort(outgoingList, compF);
		break;
		case 1:
		IncomingLinksComp compI;
		mergeSort(incomingList, compI);
		mergeSort(outgoingList, compI);
		break;
		case 2:
		OutgoingLinksComp compO;
		mergeSort(incomingList, compO);
		mergeSort(outgoingList, compO);
		break;
	}

	/* Incoming*/
	while(incomingLinksList->count() > 0){
		auto item = incomingLinksList->takeItem(0);
		delete item;
	}
	for(WebPage * page : incomingList){
		std::string pageString = page->filename();
		incomingLinksList->addItem(QString::fromStdString(pageString));
	}

	/*Outgoing*/
	while(outgoingLinksList->count() > 0){
		auto item = outgoingLinksList->takeItem(0);
		delete item;
	}
	for(WebPage * page : outgoingList){
		std::string pageString = page->filename();
		outgoingLinksList->addItem(QString::fromStdString(pageString));
	}
}

void WebPageWindow::selectIncomingLink(QListWidgetItem * item){
	unsigned int linkIndex = (unsigned int) incomingLinksList->currentRow();

	if(linkIndex >= incomingList.size())
		return;
	updateWebPage(incomingList[linkIndex]);
	
}
void WebPageWindow::selectOutgoingLink(QListWidgetItem * item){
	unsigned int linkIndex = (unsigned int) outgoingLinksList->currentRow();

	if(linkIndex >= outgoingList.size())
		return;

	updateWebPage(outgoingList[linkIndex]);
}


