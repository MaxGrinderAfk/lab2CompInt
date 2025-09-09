#include "mainwindow.h"
#include <qnamespace.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setCentralWidget(centralWidget);

    QStringList headers = {"Bus", "Device", "Func", "VendorID", "DeviceID"};
    this->pciTable = new QTableWidget{2, 5};
    this->pciTable->verticalHeader()->setVisible(false);
    this->pciTable->setHorizontalHeaderLabels(headers);
    this->pciTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->pciTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->pciTable->setMinimumSize(520, 400);

    QVBoxLayout* layout = new QVBoxLayout{centralWidget};
    layout->addWidget(this->pciTable, 0, Qt::AlignCenter);

    std::string path = "D:\\winda\\pciTxt\\pci.txt";

    Worker* newWorker = new Worker{};

    newWorker->moveToThread(workThread);
    connect(this->workThread, &QThread::started, newWorker, [newWorker, path]() {
        newWorker->work(path);
    });
    connect(this->workThread, &QThread::finished, newWorker, &QObject::deleteLater);

    connect(newWorker, &Worker::infoReady, this, [this](std::vector<PciWorker::PciDevice> info) {
        this->pciTable->setRowCount(info.size());

        for (int row = 0; row < info.size(); row++) {
            this->pciTable->setItem(row, 0, new QTableWidgetItem{QString::number(info.at(row).bus)});
            this->pciTable->setItem(row, 1, new QTableWidgetItem{QString::number(info.at(row).device)});
            this->pciTable->setItem(row, 2, new QTableWidgetItem{QString::number(info.at(row).func)});
            this->pciTable->setItem(row, 3, new QTableWidgetItem{QString::fromStdString(info.at(row).vendorId)});
            this->pciTable->setItem(row, 4, new QTableWidgetItem{QString::fromStdString(info.at(row).deviceId)});
        }
    }, Qt::QueuedConnection);

    workThread->start();
}

MainWindow::~MainWindow() {
    this->workThread->quit();
    this->workThread->wait();
    this->workThread->deleteLater();
}
