#ifndef APPLOGGER_H
#define APPLOGGER_H

#include <QObject>
#include <QFile>
#include <QPlainTextEdit>

class AppLogger : public QObject
{
    Q_OBJECT
public:
    explicit AppLogger(QObject *parent = 0,QString fileName="D:\\Pixelvalue", QPlainTextEdit *editor = 0);
    ~AppLogger();
    static AppLogger* Instance();

private:
 QFile *file;
 QPlainTextEdit *m_editor;
 bool m_showDate;

signals:

public slots:
 void write(const QString &value);
 void clear();
 void create();
};

#endif // APPLOGGER_H
