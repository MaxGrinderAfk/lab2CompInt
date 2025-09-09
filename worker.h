#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "pciworker.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr) : QObject{parent} {}

    void work(std::string path);

signals:
    void infoReady(std::vector<PciWorker::PciDevice> data);
};

#endif // WORKER_H
