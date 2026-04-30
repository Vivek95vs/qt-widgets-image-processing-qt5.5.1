#ifndef PUSH_H
#define PUSH_H

#include <QWidget>

namespace Ui {
class push;
}

class push : public QWidget
{
    Q_OBJECT

public:
    explicit push(QWidget *parent = 0);
    ~push();

public:
    Ui::push *ui;
};

#endif // PUSH_H
