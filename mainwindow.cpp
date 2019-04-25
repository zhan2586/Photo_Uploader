#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

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

void MainWindow::on_pushButton_select_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,
                                                    "Open a folder",
                                                    QDir::homePath());
    ui->statusBar->showMessage(dir + " is selected.");

}

void MainWindow::on_pushButton_copy_clicked()
{
    // int number = 15;
    QString result = "Compressed done. You photographed 15 cars today!";
    QMessageBox::information(this, "Result", result);

    QApplication::quit();
}
