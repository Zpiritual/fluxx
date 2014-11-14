#include "options.h"

Options::Options(QWidget *parent) :
    QWidget(parent)
{
    uiElements();
    parent2 = dynamic_cast<MainMenu*>(parent);
}

void Options::addProfile()
{
    if(profile_text->text() != "" && !profileExist(profile_text->text()))
    {
        user_profiles->addItem(profile_text->text());
    }
    else
    {
        if(profile_text->text() != "")
        {
            profileMessage(QString(profile_text->text() + QString(" does already exist.")));
        }
        else
        {
            profileMessage(QString("Empty profilename."));
        }

    }
    profile_text->clear();
}

void Options::removeProfile()
{
    QListWidgetItem* selected_item;
    int index = user_profiles->currentRow();
    selected_item = user_profiles->takeItem(index);
    delete selected_item;
}

void Options::enableRemoveButton()
{
    remove_profile_button->setEnabled(true);
}

void Options::ok()
{
    qDebug() << "Add ok functionality.";
    // TODO: Add functionality
    parent2->optionsBack();
}

void Options::cancel()
{
    qDebug() << "Add cancel functionality.";
    // TODO: Add functionality
    parent2->optionsBack();
}

bool Options::profileExist(const QString& profile_name) const
{
    // Check if player profile already exists
    for(int i = 0; i < user_profiles->count(); i++)
    {
        if(profile_name == user_profiles->item(i)->text())
            return true;
    }
    return false;
}

void Options::profileMessage(const QString& message) const
{
    // Display a message box
    QMessageBox* message_dialog = new QMessageBox();
    message_dialog->setWindowTitle(QString("Profile"));
    message_dialog->setText(message);
    message_dialog->show();
}

void Options::connectSignals()
{
    QObject::connect(add_profile_button, SIGNAL(clicked()), this, SLOT(addProfile()));
    QObject::connect(remove_profile_button, SIGNAL(clicked()), this, SLOT(removeProfile()));
    QObject::connect(user_profiles, SIGNAL(clicked(QModelIndex)), this, SLOT(enableRemoveButton()));
    QObject::connect(ok_button, SIGNAL(clicked()), this, SLOT(ok()));
    QObject::connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancel()));
}

void Options::uiElements()
{
    main_layout = new QVBoxLayout();
    profile_layout = new QHBoxLayout();
    finish_layout = new QHBoxLayout();
    vertical_profile_layout = new QVBoxLayout();

    user_profiles = new QListWidget();
    profile_text = new QLineEdit();

    add_profile_button = new QPushButton(QString("Add Profile"));
    remove_profile_button = new QPushButton(QString("Remove Profile"));
    ok_button = new QPushButton(QString("OK"));
    cancel_button = new QPushButton(QString("Cancel"));

    remove_profile_button->setEnabled(false);

    profile_layout->addWidget(user_profiles);
    vertical_profile_layout->addWidget(profile_text);
    vertical_profile_layout->addWidget(add_profile_button);
    vertical_profile_layout->addWidget(remove_profile_button);
    vertical_profile_layout->setAlignment(remove_profile_button, Qt::AlignTop);

    finish_layout->addWidget(ok_button);
    finish_layout->addWidget(cancel_button);

    profile_layout->addLayout(vertical_profile_layout);
    main_layout->addLayout(profile_layout);
    main_layout->addLayout(finish_layout);

    connectSignals();

    this->setLayout(main_layout);
}
