#include "ReadyQueue.hpp"
#include <stdexcept>

ReadyQueue::ReadyQueue(int priority_level, int time_quantum) : priority_level_(priority_level), time_quantum_(time_quantum) {
    
}

void ReadyQueue::addProcess(int process_id) {
    process_queue_.push(process_id);
}

int ReadyQueue::getNextProcess() {
    if (process_queue_.empty()) {
        throw std::runtime_error("No hay procesos en la cola");
    }
    int next_process = process_queue_.front();
    process_queue_.pop();
    return next_process;
}

bool ReadyQueue::isEmpty() const {
    return process_queue_.empty();
}

int ReadyQueue::getTimeQuantum() const {
    return time_quantum_;
}

int ReadyQueue::getPriorityLevel() const {
    return priority_level_;
}