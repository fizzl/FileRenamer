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

#ifndef FILETREEITEM_H
#define FILETREEITEM_H
#include <QFile>
#include <QString>
#include <QVariant>

enum SearchReplaceMode {
        Simple
    };

enum SearchReplaceRole {
        Search,
        Replace
    };


class FileTreeItem
{
    friend class FileTreeModel;

public:
    FileTreeItem(QFile *file, SearchReplaceMode mode, SearchReplaceRole role, FileTreeItem *parent = NULL);
    ~FileTreeItem();

public:
    void append(FileTreeItem *item);
    FileTreeItem *child(int which);
    int childCount() const;
    int row() const;
    QString originalName() const;
    QString replacedName() const;
    int columnCount();
public:
    QVariant data();

public:
    void update();

private:
    QFile *file;
    QList<FileTreeItem *> children;
    FileTreeItem *parent;
    QString search;
    QString replace;
    SearchReplaceMode mode;
    SearchReplaceRole role;
};

#endif // FILETREEITEM_H
