#include "MLFQPolicy.hpp"
#include "SimulationConfig.hpp"
#include "ReadyQueue.hpp"

MlfqPolicy::MlfqPolicy(std::vector<Process>& processes, SimulationConfig config)
    : processes_(processes), config_(config) {
    for (size_t i = 0; i < config_.quantums.size(); ++i) {
        queues_.emplace_back(static_cast<int>(i), config_.quantums[i]);
    }
}

int MlfqPolicy::getNextProcess()  {
    for (size_t i = 0; i < queues_.size(); ++i) {
        if (!queues_[i].isEmpty()) {
            int process_index = queues_[i].getNextProcess();
            return process_index;
        }
    }
    return -1; 
}

void MlfqPolicy::onProcessArrival(int process_index) {
    moveToQueue(process_index, 0);
}

void MlfqPolicy::onTick(int current_tick) {
    if (current_tick > 0 && current_tick % config_.boost_interval == 0) {
        for (size_t i = 1; i < queues_.size(); ++i) {
            while (!queues_[i].isEmpty()) {
                int process_index = queues_[i].getNextProcess();
                moveToQueue(process_index, 0);
            }
        }
    }
}

void MlfqPolicy::onQuantumExpired(int process_index) {
    int current_queue = processes_[process_index].currentQueue();
    if (current_queue < static_cast<int>(queues_.size()) - 1) {
        moveToQueue(process_index, current_queue + 1);
    } else {
        moveToQueue(process_index, current_queue);
    }
}

void MlfqPolicy::moveToQueue(int process_index, int new_queue) {
    processes_[process_index].changeQueue(new_queue);
    processes_[process_index].resetQuantum();
    queues_[new_queue].addProcess(process_index);
}

bool MlfqPolicy::shouldPreempt(int process_index) const {
    int queue_index = processes_[process_index].currentQueue();
    int time_quantum = queues_[queue_index].getTimeQuantum();
    return processes_[process_index].quantumUsed() >= time_quantum;
}