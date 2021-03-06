#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_select_clicked();

    void on_label_number_linkActivated(const QString &link);

    void on_pushButton_2_clicked();

    void on_pushButton_copy_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
