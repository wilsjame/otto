#include <QtWidgets>  
#include <QDebug>
#include <QString>

#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include <fstream> 
#include <string>

#include <regex>

#include "otto.h"

//TODO widgets... create shortcuts, kill motive, etc...

Otto::Otto(QWidget *parent)
	: QDialog(parent)
{
	/* create child widgets */
	// find build 
	findBuildButton = new QPushButton(tr("Find Build"));
	findBuildResult = new QPlainTextEdit("");
	
	// exit otto
	closeButton = new QPushButton(tr("Close"));

	/* make connections */
	connect(findBuildButton, SIGNAL(clicked()),
			this, SLOT(findBuildClicked()));
	connect(closeButton, SIGNAL(clicked()),
			this, SLOT(close()));

	/* layout child widgets */
	QVBoxLayout *middleLayout = new QVBoxLayout;
	middleLayout->addWidget(findBuildButton);
	middleLayout->addWidget(closeButton);
	middleLayout->addWidget(findBuildResult);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(middleLayout);
	setLayout(mainLayout);

	/* misc */
	setWindowTitle(tr("otto"));
	setFixedHeight(sizeHint().height());
}

/* slots */
void Otto::findBuildClicked() 
{
	std::cout << "trace";
}
