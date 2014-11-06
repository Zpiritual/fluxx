#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QtWidgets>

class Options : public QWidget
{
    Q_OBJECT
public:
    explicit Options(QWidget *parent = 0);

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

    bool profileExist(const QString&) const;
    void profileMessage(const QString&) const;
    void connectSignals();
    void initializeWidgets();

signals:

public slots:
    void addProfile();
    void removeProfile();
    void enableRemoveButton();
    void ok();
    void cancel();
};

#endif // OPTIONS_H
