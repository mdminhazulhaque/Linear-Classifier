#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <math.h>

namespace Ui {
class Dialog;
class Group;
}

class Group
{
public:
    Group(int _x, int _y, char _l)
    {
        x = _x;
        y = _y;
        l = _l;
    }

    int x;
    int y;
    char l;
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void drawPoint(const Group &group);
    void addToGroup(const Group &group);

    void classifyNearest(Group *group);
    void classifyRouge(Group *group);
    void addSampleData();
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::Dialog *ui;
    char labelClass1;
    char labelClass2;
    QList<Group> groups;
};

#endif // DIALOG_H
