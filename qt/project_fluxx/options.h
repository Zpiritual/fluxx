//Class shown in the main menu wndow that add profiles, remove profiles and show profilestats.

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QtWidgets>
#include "mainmenu.h"

class Options : public QWidget
{
    Q_OBJECT
public:
    explicit Options(const std::vector<Profile>&, QWidget *parent = 0);
    ~Options();
private:
    QVBoxLayout* main_layout;
    QHBoxLayout* profile_layout;
    QVBoxLayout* vertical_profile_layout;
    QHBoxLayout* finish_layout;

    QListWidget* user_profiles;
    QLineEdit*  profile_text;

    QPushButton* add_profile_button;
    QPushButton* remove_profile_button;

    QPushButton* ok_button;
    QPushButton* cancel_button;

    QLabel* profile_stats;

    MainMenu* parent2;

    std::vector<Profile> profiles;

    bool profileExist(const QString&) const;
    void message(const QString&, const QString&) const;
    void connectSignals();
    void uiElements();

    void addProfile(const Profile&);
    void removeProfile(const Profile&);
    void addToProfiles();

public slots:
    void addProfile();
    void removeProfile();
    void enableRemoveButton();
    void enableAddButton();
    void ok();
    void cancel();
    void showProfileStats();
};

#endif // OPTIONS_H
