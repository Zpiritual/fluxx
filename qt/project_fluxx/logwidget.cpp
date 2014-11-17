#include "logwidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent)
{
   layout = new QVBoxLayout();
   log_label = new QLabel();

   layout->addWidget(log_label);

   log_label->setText(QString("Här är massa logg\nÄnnu mera log\n Log log log sinus och cosinus"));

   this->setLayout(layout);
}

LogWidget::~LogWidget(){
}
