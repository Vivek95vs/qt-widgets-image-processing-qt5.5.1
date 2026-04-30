#ifndef MYQT_H
#define MYQT_H

#include <QObject>

class MYqt: public QObject
{
        Q_OBJECT
public:
    MYqt();

public slots:
    void buttonClicked();
};

#endif // MYQT_H
