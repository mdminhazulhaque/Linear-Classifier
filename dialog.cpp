#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    labelClass1 = 'X';
    labelClass2 = 'O';

    addSampleData();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::drawPoint(const Group& group)
{
    QLabel *label = new QLabel(this);
    label->setText(QString(group.l));
    label->show();
    label->setGeometry(group.x, group.y, label->width(), label->height());
}

void Dialog::addToGroup(const Group &group)
{
    groups.append(group);
    drawPoint(group);
}

void Dialog::classifyNearest(Group *group)
{
    qreal dG1 = 999;
    qreal dG2 = 999;

    foreach(const Group &g, groups)
    {
        qreal d = sqrt(pow(g.x - group->x, 2) + pow(g.y - group->y, 2));

        if(g.l == labelClass1 && d < dG1)
            dG1 = d;

        else if(g.l == labelClass2 && d < dG2)
            dG2 = d;
    }

    if(dG2 > dG1)
        group->l = labelClass1;
    else
        group->l = labelClass2;
}

void Dialog::classifyRouge(Group *group)
{
    qreal dG1 = 0;
    qreal dG2 = 0;

    int dC1 = 0;
    int dC2 = 0;

    foreach(const Group &g, groups)
    {
        qreal d = sqrt(pow(g.x - group->x, 2) + pow(g.y - group->y, 2));

        if(g.l == labelClass1)
        {
            dG1 += d;
            dC1++;
        }
        else if(g.l == labelClass2)
        {
            dG2 += d;
            dC2++;
        }
    }

    qreal avg1 = dG1/dC1;
    qreal avg2 = dG2/dC2;

    if(avg1 < avg2)
        group->l = labelClass1;
    else
        group->l = labelClass2;
}

void Dialog::addSampleData()
{
    addToGroup(Group(35, 14, labelClass1));
    addToGroup(Group(33, 69, labelClass1));
    addToGroup(Group(99, 68, labelClass1));
    addToGroup(Group(77, 32, labelClass1));

    addToGroup(Group(297, 251, labelClass2));
    addToGroup(Group(320, 220, labelClass2));
    addToGroup(Group(365, 257, labelClass2));
    addToGroup(Group(351, 170, labelClass2));
}

void Dialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    point.setY(point.y()-15); // remove window top bar height

    Group born(point.x(), point.y(), '+');

    if(ui->radioButton->isChecked())
        classifyNearest(&born);
    else
        classifyRouge(&born);

    addToGroup(born);
    setWindowTitle(QString("Added (%1,%2) to Group %3").arg(born.x).arg(born.y).arg(born.l));

}
