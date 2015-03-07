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

#include "filetreeitem.h"
#include <QtAlgorithms>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QFileInfo>

FileTreeItem::FileTreeItem(QFile *file, SearchReplaceMode mode, SearchReplaceRole role, FileTreeItem *parent)
{
    this->file = file;
    this->mode = mode;
    this->parent = parent;
    this->role = role;
}

FileTreeItem::~FileTreeItem()
{
    qDeleteAll(children);
    delete file;
}


void FileTreeItem::append(FileTreeItem *item)
{
    children.append(item);
}

FileTreeItem *FileTreeItem::child(int which)
{
    return children.value(which);
}

int FileTreeItem::childCount() const
{
    return children.count();
}

int FileTreeItem::row() const
{
    if(parent != NULL)
    {
        return parent->children.indexOf(const_cast<FileTreeItem*>(this));
    }
    return 0;
}

int FileTreeItem::columnCount()
{
    return 1;
}

QVariant FileTreeItem::data()
{
    QVariant ret;
    if(role == Search) {
        ret = originalName();
    }
    else
    {
        ret = replacedName();
    }
    QFileInfo info(ret.toString());
    return info.fileName();
}

QString FileTreeItem::originalName() const
{
    return file->fileName();
}

QString FileTreeItem::replacedName() const
{
    QString ret = file->fileName();
    const QChar *rep = replace.begin();
    for(QString::const_iterator itr(search.begin()); itr != search.end(); itr++)
    {
        ret = ret.replace(*itr, *rep);
    }
    return ret;
}

void FileTreeItem::update()
{
    qDeleteAll(children);
    qDebug() << file->fileName();
    QFileInfo info(*file);
    if(info.isDir())
    {
        qDebug() << "Is dir ";
        QDir dir;
        dir.setFilter(QDir::AllEntries|QDir::NoDotAndDotDot|QDir::NoSymLinks);
        dir.setSorting(QDir::Time);
        dir.setPath(info.absoluteFilePath());
        QStringList list = dir.entryList();
        for(int i=0;i<list.count();i++)
        {
            QString fn = list.at(i);
            if(fn == "." || fn == "..")
            {
                continue;
            }
            qDebug() << fn;
            QFile *newFile = new QFile(dir.absoluteFilePath(fn));
            FileTreeItem *newItem = new FileTreeItem(newFile, mode, role, this);
            append(newItem);
            newItem->update();
        }
    }
}
