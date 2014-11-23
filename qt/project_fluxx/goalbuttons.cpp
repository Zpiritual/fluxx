#include "goalbuttons.h"

GoalButtons::GoalButtons(QWidget *parent) :
    QWidget(parent)
{
    layout = new QHBoxLayout();

    this->setLayout(layout);

}

void GoalButtons::updateCards(const std::vector<CardID> &)
{

}

GoalButtons::~GoalButtons()
{
}
