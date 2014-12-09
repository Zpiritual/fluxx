#include "options.h"

Options::Options(const std::vector<Profile>& prfiles, QWidget *parent) :
    QWidget(parent)
{
    uiElements();
    parent2 = dynamic_cast<MainMenu*>(parent);

    profiles = prfiles;

    for(unsigned int i = 0; i < profiles.size(); i++)
    {
        user_profiles->addItem(QString::fromStdString(profiles.at(i).getName()));
    }
}

Options::~Options()
{
    delete user_profiles;
    delete add_profile_button;
    delete remove_profile_button;
    delete ok_button;
    delete cancel_button;
    delete vertical_profile_layout;
    delete profile_layout;
    delete finish_layout;
    delete main_layout;
}

void Options::addProfile()
{
    if(profile_text->text() != "" && !profileExist(profile_text->text()))
    {
        user_profiles->addItem(profile_text->text());
        addProfile(Profile(profile_text->text().toStdString()));
    }
    else
    {
        if(profile_text->text() != "")
        {
            message(QString("Options"), QString(profile_text->text() + QString(" does already exist.")));
        }
        else
        {
            message(QString("Options"), QString("Empty profilename."));
        }

    }
    profile_text->clear();
}

void Options::removeProfile()
{
    QListWidgetItem* selected_item;
    int index = user_profiles->currentRow();
    selected_item = user_profiles->takeItem(index);
    removeProfile(Profile(selected_item->text().toStdString()));
    delete selected_item;

    user_profiles->clearSelection();
    remove_profile_button->setEnabled(false);
}

void Options::enableRemoveButton()
{
    remove_profile_button->setEnabled(true);
}

void Options::enableAddButton()
{
    if(profile_text->text() == "")
    {
        add_profile_button->setEnabled(false);
    }
    else
    {
        add_profile_button->setEnabled(true);
    }
}

void Options::ok()
{
    qDebug() << "Add ok functionality.";
    // TODO: Add functionality
    if(parent2 != nullptr)
    {
        parent2->setProfiles(profiles);
        parent2->optionsBack();
    }
    else
    {
        message(QString("Error"), QString("parent2 does not exist"));
    }
}

void Options::cancel()
{
    qDebug() << "Add cancel functionality.";
    // TODO: Add functionality
    if(parent2 != nullptr)
    {
        parent2->optionsBack();
    }
    else
    {
        message(QString("Error"), QString("parent2 does not exist"));
    }
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

void Options::message(const QString& title, const QString& message) const
{
    // Display a message box
    QMessageBox message_dialog;
    message_dialog.setWindowTitle(title);
    message_dialog.setText(message);
    message_dialog.exec();
}

void Options::connectSignals()
{
    QObject::connect(add_profile_button, SIGNAL(clicked()), this, SLOT(addProfile()));
    QObject::connect(remove_profile_button, SIGNAL(clicked()), this, SLOT(removeProfile()));
    QObject::connect(user_profiles, SIGNAL(clicked(QModelIndex)), this, SLOT(enableRemoveButton()));
    QObject::connect(ok_button, SIGNAL(clicked()), this, SLOT(ok()));
    QObject::connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(profile_text, SIGNAL(textChanged(QString)), this, SLOT(enableAddButton()));
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
    add_profile_button->setEnabled(false);

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

void Options::addProfile(const Profile& profile)
{
    profiles.push_back(profile);
}

void Options::removeProfile(const Profile& profile)
{
    for(auto it = profiles.begin(); it != profiles.end(); ++it)
    {
        if(it->getName() == profile.getName())
        {
            if(it == profiles.end() - 1)
            {
                profiles.pop_back();
                return;
            }
            profiles.erase(it);
            return;
        }
    }
}
