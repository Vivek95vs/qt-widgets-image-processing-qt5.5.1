#include "DicomTreeItem.h"

#include <QStringList>


DicomTreeItem::DicomTreeItem(const QVector<QVariant> &data, DicomTreeItem *parent)
{
    parentItem = parent;
    itemData = data;
}

DicomTreeItem::~DicomTreeItem()
{
    qDeleteAll(childItems);
}

DicomTreeItem *DicomTreeItem::child(int number)
{
    return childItems.value(number);
}

int DicomTreeItem::childCount() const
{
    return childItems.count();
}

int DicomTreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<DicomTreeItem*>(this));

    return 0;
}

int DicomTreeItem::columnCount() const
{
    return itemData.count();
}

QVariant DicomTreeItem::data(int column) const
{
    return itemData.value(column);
}

bool DicomTreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        DicomTreeItem *item = new DicomTreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

bool DicomTreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach(DicomTreeItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}

DicomTreeItem *DicomTreeItem::parent()
{
    return parentItem;
}

bool DicomTreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

bool DicomTreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach(DicomTreeItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}

bool DicomTreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}
