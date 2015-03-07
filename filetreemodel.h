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

#ifndef FILETREEMODEL_H
#define FILETREEMODEL_H

#include <QAbstractItemModel>
#include <QFile>

#include "filetreeitem.h"

class FileTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    FileTreeModel(QFile *root, SearchReplaceRole role, QObject *parent = NULL);
    ~FileTreeModel();

public:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
public:
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

public slots:
    void update();

private:
    QFile *rootData;
    FileTreeItem *rootItem;
    SearchReplaceRole role;
};

#endif // FILETREEMODEL_H
