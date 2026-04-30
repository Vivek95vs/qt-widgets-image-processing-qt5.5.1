#include "DicomDirTreeModel.h"

#include <QtWidgets>
#include "DicomTreeItem.h"

DicomDirTreeModel::DicomDirTreeModel(const QStringList &headers, const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{

    QVector<QVariant> rootData;
    foreach(QString header, headers)
        rootData << header;

    rootItem = new DicomTreeItem(rootData);

    setupModelData(data.split(QString("\n")), rootItem);
}

DicomDirTreeModel::DicomDirTreeModel(const QStringList& headers, const DicomPatient& patient, QObject* parent)
{
    QVector<QVariant> rootData;
    foreach(QString header, headers)
        rootData << header;

    rootItem = new DicomTreeItem(rootData);

    setupModelData(patient, rootItem);
}


DicomDirTreeModel::~DicomDirTreeModel()
{
    delete rootItem;
}

int DicomDirTreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}

QVariant DicomDirTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    DicomTreeItem *item = getItem(index);

    return item->data(index.column());
}

Qt::ItemFlags DicomDirTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

DicomTreeItem *DicomDirTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        DicomTreeItem *item = static_cast<DicomTreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

int DicomDirTreeModel::getLevel(const QModelIndex & index) const
{
    DicomTreeItem * p_dicom_tree_item = this->getItem(index);
    int level = 0;
    while (p_dicom_tree_item->parent() != NULL)
    {
        level++;
        p_dicom_tree_item = p_dicom_tree_item->parent();
    }
    return level;
}


QVariant DicomDirTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex DicomDirTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
    //! [5]

    //! [6]
    DicomTreeItem *parentItem = getItem(parent);

    DicomTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

bool DicomDirTreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool DicomDirTreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    DicomTreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

QModelIndex DicomDirTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DicomTreeItem *childItem = getItem(index);
    DicomTreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool DicomDirTreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool DicomDirTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    DicomTreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

int DicomDirTreeModel::rowCount(const QModelIndex &parent) const
{
    DicomTreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}

bool DicomDirTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    DicomTreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool DicomDirTreeModel::setHeaderData(int section, Qt::Orientation orientation,const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void DicomDirTreeModel::setupModelData(const QStringList &lines, DicomTreeItem *parent)
{
    QList<DicomTreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].at(position) != ' ')
                break;
            ++position;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount() - 1);
                    indentations << position;
                }
            }
            else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            DicomTreeItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }

        ++number;
    }
}

void DicomDirTreeModel::setupModelData(const DicomPatient & patient, DicomTreeItem * parent)
{
    QVector<QVariant> PatientData;
    PatientData << QString::fromStdString(patient.PatientID);
    PatientData << QString::fromStdString(patient.PatientName);
    parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
    for (int column = 0; column < PatientData.size(); ++column)
        parent->child(parent->childCount() - 1)->setData(column, PatientData[column]);
    for (int i = 0; i < patient.StudyList.size(); i++)
    {
        QVector<QVariant> StudyData;
        StudyData << QString::fromStdString(patient.StudyList[i]->StudyId);
        StudyData << QString::fromStdString(patient.StudyList[i]->ModulationType);
        parent->child(0)->insertChildren(parent->child(0)->childCount(), 1, rootItem->columnCount());
        for (int column = 0; column < StudyData.size(); ++column)
            parent->child(0)->child(parent->childCount() - 1)->setData(column, StudyData[column]);
        for (int j = 0; j < patient.StudyList[i]->SeriesList.size(); j++)
        {
            QVector<QVariant> SeriesData;
            SeriesData << QString::fromStdString(patient.StudyList[i]->SeriesList[j]->SeriseNumber);
            SeriesData << QString::fromStdString(patient.StudyList[i]->SeriesList[j]->Manufacturer);
            parent->child(0)->child(i)->insertChildren(parent->child(0)->child(i)->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < SeriesData.size(); ++column)
                parent->child(0)->child(i)->child(parent->child(0)->child(i)->childCount() - 1)->setData(column, SeriesData[column]);
            for (int k = 0; k < patient.StudyList[i]->SeriesList[j]->ImageList.size(); k++)
            {
                QVector<QVariant> ImageData;
                QString temp = "Img"; temp.append(QString::fromStdString(std::to_string(k)));
                ImageData << temp;
                ImageData << QString::fromStdString(patient.StudyList[i]->SeriesList[j]->ImageList[k]->ReferencedFileID);
                parent->child(0)->child(i)->child(j)->insertChildren(parent->child(0)->child(i)->child(j)->childCount(), 1, rootItem->columnCount());
                for (int column = 0; column < ImageData.size(); ++column)
                    parent->child(0)->child(i)->child(j)->child(parent->child(0)->child(i)->child(j)->childCount() - 1)->setData(column, ImageData[column]);
            }
        }
    }
}
