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
#include <QDesktopServices>
#include <QtMath>

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
QString name = "Andy";
QString link = "https://wetransfer.com";

float carNumber;

void createNewFolder(){
    QDate today = QDate::currentDate();
    QString newFolder = today.toString();
    QDir dir;
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

void countNumber(){
    QDir dir( destDir );
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    int photoNumber = dir.count();
    carNumber = photoNumber / 25.0;
    qDebug() << "There are " << photoNumber << " photos in detination folder.";

    // round number to integer
    int carNumberInt = qFloor(carNumber);
    float carNumberDecimal = carNumber - carNumberInt;
    qDebug() << "Integer part is " << carNumberInt;
    qDebug() << "Decimal part is " << carNumberDecimal;
    if (carNumberDecimal < 0.5){
        carNumber = carNumberInt;
    }
    else{
        carNumber = carNumberInt + 1;
    }
    qDebug() << "There are " << carNumber << " cars in detination folder.";
}

void MainWindow::on_pushButton_copy_clicked()
{
    createNewFolder();
    copyPath(srcDir, destDir);

    QString zipFile = destDir + "_" + name + ".zip";
    compressDir(zipFile, destDir);
    QString outputTip = "Compressed done as " + zipFile;
    QMessageBox::information(this, "Target file", outputTip);

    countNumber();
    QString str1 = " cars today!";
    QString resultTip = "You photographed " + QString::number(carNumber) + str1;
    QMessageBox::information(this, "Result", resultTip);

    QDesktopServices::openUrl(QUrl("file:///E:/Dealership",
                                   QUrl::TolerantMode));
    QDesktopServices::openUrl(QUrl(link));
    QApplication::quit();
}

