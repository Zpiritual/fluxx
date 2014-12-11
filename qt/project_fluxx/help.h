//Empty class that should've contained help about how to play the game.

#ifndef HELP_H
#define HELP_H

#include <QWidget>

class Help : public QWidget
{
    Q_OBJECT
public:
    explicit Help(QWidget *parent = 0);
};

#endif // HELP_H
