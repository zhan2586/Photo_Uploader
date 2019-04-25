#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QDate>
#include <QFile>
#include <QTextStream>

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
    QDir dir = destDir;
    destDir = dir.mkpath("E:/Dealership/" + newFolder);
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

    foreach (QString f, dir.entryList(QDir::Files)) {
        QString srcItemPath = srcDir + "/" + f;
        QString dstItemPath = destDir + "/" + f;
        QFile::copy(srcItemPath, dstItemPath);
    }
}

void MainWindow::on_pushButton_select_clicked()
{
    srcDir = QFileDialog::getExistingDirectory(this,
                                                    "Open a folder",
                                                    QDir::homePath());
    ui->statusBar->showMessage(srcDir + " is selected.");

}

void MainWindow::on_pushButton_copy_clicked()
{
    createNewFolder();
    copyPath(srcDir, destDir);
    QTextStream out(&srcDir);
    QString text = ui->plainTextEdit->toPlainText();
    out << text;
    QMessageBox::information(this, "srcDir", srcDir);
    QString result = "Compressed done. You photographed 15 cars today!";
    QMessageBox::information(this, "Result", result);

    QApplication::quit();
}

/*int carNumber(fileNumber){
    number = fileNumber / 25;
    (int)number; // round number to integer

    return number;
}*/
