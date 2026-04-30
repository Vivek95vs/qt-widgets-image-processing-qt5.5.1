#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include<QTcpServer>
#include<QTcpSocket>

class client : public QObject
{
public:
    client();
};

#endif // CLIENT_H
