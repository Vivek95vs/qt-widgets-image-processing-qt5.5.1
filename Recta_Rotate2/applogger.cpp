#include "applogger.h"
#include <QDebug>
#include <QDateTime>
#include <QTextStream>
#include <iostream>

Q_GLOBAL_STATIC(AppLogger,log_Instance)

AppLogger::AppLogger(QObject *parent, QString fileName, QPlainTextEdit *editor) : QObject(parent)
{
    m_editor = editor;
    m_showDate = true;
    if (!fileName.isEmpty())
    {
        file = new QFile;
        file->setFileName(fileName);
        file->open(QIODevice::Append | QIODevice::Text);
        qDebug()<<"files size"<<file->size();
        if(file->size()>=2000000)
        {
            file->resize(0);
        }
    }
}

AppLogger::~AppLogger()
{
    if (file != 0)
        file->close();
    delete file;
}

AppLogger *AppLogger::Instance()
{
    if(log_Instance){
        //qDebug()<<"log_Instance instance exists";
        return log_Instance;
    }else{
        return NULL;
        //qDebug()<<"log_Instance instance not created";
    }

}

void AppLogger::write(const QString &value)
{
    QString text = value;// + "";
    if (m_showDate)
        text = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ") + text +"\n";
    QTextStream out(file);
    out.setCodec("UTF-8");
    if (file != 0) {
        out << text;
    }
    if (m_editor != 0)
        m_editor->appendPlainText(text);
}

void AppLogger::clear()
{

    QFile fileModify("D:\\data.txt");
    if (!fileModify.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate))
    {
        qDebug()<<" file emptying failed";
    }
    fileModify.close();

}


