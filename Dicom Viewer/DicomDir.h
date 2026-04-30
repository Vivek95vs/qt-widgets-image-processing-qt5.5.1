#ifndef DICOMDIR_H
#define DICOMDIR_H

#include <QWidget>
#include "ui_DicomDir.h"
#include "DicomDataBase.h"

class PatientMsg
{
public:
    QString FileID;
    QString PatientID;
    QString PatientName;
    QString BirthDate;
    QString Gender;
public:
    PatientMsg()
    {
        FileID = "NULL";
        PatientID = "NULL";
        PatientName = "NULL";
        BirthDate = "NULL";
        Gender = "NULL";
    }
};
class DicomDir : public QWidget
{
    Q_OBJECT

public:
    DicomDir(QWidget *parent = Q_NULLPTR);
    void InitDirExplorerFromDirPath(QString DicomDirFidlePath);
    void InitDirExplorerFromSingleFilePath(QString ImageFilePath);
    void InitDirExplorerFromSeriesPath(QString SeriesPath);
    ~DicomDir();
private:
    Ui::DicomDir ui;
    DicomDataBase* m_database;
    void ConstructsTable();
signals:
    void sendData(QString Id);
public slots:
    void OnPushOk();
    void OnPushCancel();
};

#endif // DICOMDIR_H
