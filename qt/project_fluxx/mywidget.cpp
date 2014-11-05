#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    newGameButton = new QPushButton{QString("New Game")};
    continueGameButton = new QPushButton{QString("Continue Game")};
    optionsButton = new QPushButton{QString("Options")};
    exitButton = new QPushButton{QString("Exit")};

    mainLayout = new QGridLayout();
    horizontalLayout = new QHBoxLayout();
    verticalLayout = new QVBoxLayout();

    mainLayout->addLayout(horizontalLayout, 0, 0);
    mainLayout->addLayout(verticalLayout, 1, 0);
    this->setLayout(mainLayout);
    this->setWindowTitle(QString("MainMenu"));

    horizontalLayout->addWidget(newGameButton);
    horizontalLayout->addWidget(continueGameButton);
    horizontalLayout->addWidget(optionsButton);
    horizontalLayout->addWidget(exitButton);

    QObject::connect(newGameButton, SIGNAL(clicked()), this, SLOT(newGame()));
    QObject::connect(continueGameButton, SIGNAL(clicked()), this, SLOT(continueGame()));
    QObject::connect(optionsButton, SIGNAL(clicked()), this, SLOT(options()));
    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(changeExitLayout()));
}

MyWidget::~MyWidget()
{
}

void MyWidget::newGame()
{
    QMessageBox* messageBox = new QMessageBox();
    messageBox->setWindowTitle("New Game");
    messageBox->setText("A New Game Has Been Started!");
    messageBox->show();
    this->hide();

    int ret = messageBox->exec();
    if(ret != 0)
    {
        messageBox->close();
        this->show();
    }
}

void MyWidget::continueGame()
{
    QMessageBox* messageBox = new QMessageBox();
    messageBox->setWindowTitle("Continue Game");
    messageBox->setText("Lastest Game Session is continued!");
    messageBox->show();
    this->hide();

    int ret = messageBox->exec();
    if(ret != 0)
    {
        messageBox->close();
        this->show();
    }
}

void MyWidget::options()
{
    QMessageBox* messageBox = new QMessageBox();
    messageBox->setWindowTitle("Options");
    messageBox->setText("Options are avaliable!");
    messageBox->show();
    this->hide();

    int ret = messageBox->exec();
    if(ret != 0)
    {
        messageBox->close();
        this->show();
    }
}

void MyWidget::exit()
{
    this->close();
}

void MyWidget::changeExitLayout()
{
    if(horizontalLayout->indexOf(exitButton) != -1)
    {
        verticalLayout->addWidget(exitButton);
        //horizontalLayout->removeWidget(exitButton);
    }
    else
    {
        horizontalLayout->addWidget(exitButton);
        //verticalLayout->removeWidget(exitButton);
    }
}
