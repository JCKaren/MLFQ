    #include "SimulationEngine.hpp"
    #include <iostream>

    SimulationEngine::SimulationEngine(std::vector<Process> processes, IResultsExporter& results_exporter)
        : processes_(processes), queues_(3), results_exporter_(results_exporter)
    {

    }

    void SimulationEngine::run() {
        while (finished_count_ < processes_.size()) {
            arrivalPhase();
            priorityBoostPhase();
            selectionPhase();
            if (running_ != -1) {
                markFirstResponsePhase();
                consumeTickPhase();
            }

            current_tick_++;
            if (running_ != -1) {
                checkCompletionTickPhase();
            }
        }
        
        results_exporter_.exportResults(processes_);
    }


    void SimulationEngine::arrivalPhase(){
        for (size_t i = 0; i < processes_.size(); ++i) {
            if (processes_[i].arrivalTime() == current_tick_) {
                queues_[0].push_back(i);
            }
        }
    }

    void SimulationEngine::selectionPhase() {
        if (running_ != -1) {
            return;
        }
        for (size_t i = 0; i < queues_.size(); ++i) {
            if (!queues_[i].empty()) {
                running_ = queues_[i].front();
                queues_[i].pop_front();
                processes_[running_].resetQuantum();
                break;
            }
        }
    }

    void SimulationEngine::markFirstResponsePhase() {
        if (running_ != -1 && !processes_[running_].hasResponded()) {
            processes_[running_].firstExecution(current_tick_);
        }
    }

    void SimulationEngine::consumeTickPhase(){
        processes_[running_].consumeTick();
    }

    void SimulationEngine::checkCompletionTickPhase() {
        if (processes_[running_].isFinished()) {
            processes_[running_].finishProcess(current_tick_);
            running_ = -1;
            finished_count_++;
        } else if (processes_[running_].quantumUsed() >= quantums_[processes_[running_].currentQueue()]) {
            int current_queue = processes_[running_].currentQueue();
            if (current_queue < static_cast<int>(queues_.size()) - 1) {
                processes_[running_].changeQueue(current_queue + 1);
            }
            queues_[processes_[running_].currentQueue()].push_back(running_);
            running_ = -1;
        }
    }

    void SimulationEngine::priorityBoostPhase() {
        if (current_tick_ > 0 && current_tick_ % BOOST_INTERVAL == 0){
            for (size_t i = 1; i < queues_.size(); ++i) {
                while (!queues_[i].empty()) {
                    int idx = queues_[i].front();
                    queues_[i].pop_front();
                    processes_[idx].changeQueue(0);
                    queues_[0].push_back(idx);
                    processes_[idx].resetQuantum();
                    }
                }
        }
    }