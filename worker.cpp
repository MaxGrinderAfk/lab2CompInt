#include "worker.h"

void Worker::work(std::string path) {
    PciWorker worker(path);

    emit infoReady(worker.getDevices());
}
