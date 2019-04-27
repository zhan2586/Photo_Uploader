#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <JlCompress.h>

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

QString srcDir;
QString destDir;

void createNewFolder(){
    QDate today = QDate::currentDate();
    QString newFolder = today.toString();
    QDir dir;
    // destDir = dir.mkpath("E:/Dealership/" + newFolder);
    dir.mkpath("E:/Dealership/" + newFolder);
    destDir = "E:/Dealership/" + newFolder;
    qDebug() << "Destination folder is: " << destDir;
}

void copyPath(QString srcDir, QString destDir)
{
    QDir dir(srcDir);
    if (! dir.exists())
        return;

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = destDir + QDir::separator() + d;
        dir.mkpath(dst_path);
        copyPath(srcDir+ QDir::separator() + d, dst_path);
    }

    foreach (QString file, dir.entryList(QDir::Files)) {       
        qDebug() << "Copy files from " << srcDir << " to " << destDir;
        QFile::copy(srcDir+ QDir::separator() + file, destDir+ QDir::separator() + file);
    }
}

void MainWindow::on_pushButton_select_clicked()
{
    srcDir = QFileDialog::getExistingDirectory(this,
                                                    "Open a folder",
                                                    QDir::homePath());
    qDebug() << "Selected directory: " << srcDir;
    ui->statusBar->showMessage(srcDir + " is selected.");

}

void compressDir(QString zipFile, QString destDir){
    if(JlCompress::compressDir(zipFile, destDir)){
        qDebug()<<"Created: " << zipFile;
    }
    else{
        qDebug() << "Could not create: ";
    }
}

void MainWindow::on_pushButton_copy_clicked()
{
    createNewFolder();
    copyPath(srcDir, destDir);

    QString zipFile = destDir + ".zip";
    compressDir(zipFile, destDir);

    QMessageBox::information(this, "destination", destDir);
    QString result = "Compressed done. You photographed 15 cars today!";
    QMessageBox::information(this, "Result", result);

    QApplication::quit();
}

/* carNumber(destDir){
    int number = destDir.count() / 25;
    qDebug() << "There are " << number << " photos in destDir.";
    (int)number; // round number to integer

    return number;
}*/
