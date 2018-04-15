#include <base/log.h>
#include <AsynchronousCloseMonitor.h>

void AsynchronousCloseMonitor::init() {
    Genode::warning(__func__, ": Not implemented");
}

bool AsynchronousCloseMonitor::wasSignaled() const {
    Genode::warning(__func__, ": Not implemented");
    return false;
}

void AsynchronousCloseMonitor::signalBlockedThreads(int fd) {
    Genode::warning(__func__, ": Not implemented");
}

AsynchronousCloseMonitor::AsynchronousCloseMonitor(int fd) {
    Genode::warning(__func__, ": Not implemented");
}

AsynchronousCloseMonitor::~AsynchronousCloseMonitor() { }
