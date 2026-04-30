#ifndef QTCPSERVER_H
#define QTCPSERVER_H

#include <QObject>

class QTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit QTcpServer(QObject *parent = 0);

signals:

public slots:
};

#endif // QTCPSERVER_H
