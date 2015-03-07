/**
 * Copyright Lassi Marttala, Maxpower Inc (2015)
 * <fizzl@fizzl.net>
 *
 * This file is part of FileRenamer.
 *
 *   FileRenamer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   FileRenamer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with FileRenamer.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include "filetreemodel.h"

FileTreeModel::FileTreeModel(QFile *root, SearchReplaceRole role, QObject *parent)
    : QAbstractItemModel(parent)
{
    this->rootData = root;
    this->rootItem = new FileTreeItem(rootData, Simple, role);
    this->role = role;
}

FileTreeModel::~FileTreeModel()
{
    delete rootItem;
}

QModelIndex FileTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    FileTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<FileTreeItem*>(parent.internalPointer());

    FileTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex FileTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    FileTreeItem *childItem = static_cast<FileTreeItem*>(index.internalPointer());
    FileTreeItem *parentItem = childItem->parent;

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}


int FileTreeModel::rowCount(const QModelIndex &parent) const
{
    FileTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<FileTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int FileTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<FileTreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant FileTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    FileTreeItem *item = static_cast<FileTreeItem*>(index.internalPointer());

    return item->data();
}

Qt::ItemFlags FileTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant FileTreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        this->rootItem->data();
    }
    return QVariant();
}

void FileTreeModel::update()
{
    rootItem->update();
}
