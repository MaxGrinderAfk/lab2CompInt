#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QThread>
#include <QStringList>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QChar>
#include "worker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    QWidget* centralWidget = new QWidget{this};
    QTableWidget* pciTable;

    QThread* workThread = new QThread{this};
};
#endif // MAINWINDOW_H
