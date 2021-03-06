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
 *   Foobar is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with FileRenamer.  If not, see <http://www.gnu.org/licenses/>.
 **/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filetreemodel.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Folder_triggered()
{
    QFileDialog opts;
    QString fn = QFileDialog::getExistingDirectory(this, tr("Open Folder"), tr("~"));
    QFile *rootFile = new QFile(fn);
    FileTreeModel *model = new FileTreeModel(rootFile, Search, ui->searchTree);
    model->update();
    ui->searchTree->setModel(model);
}
