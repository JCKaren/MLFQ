    #include "SimulationEngine.hpp"

    SimulationEngine::SimulationEngine(std::vector<Process> processes, IResultsExporter& results_exporter, SimulationConfig config)
        : processes_(processes), results_exporter_(results_exporter), config_(config)
    {
        for (size_t i = 0; i < config_.quantums.size(); ++i) {
            ready_queues_.emplace_back(static_cast<int>(i), config_.quantums[i]);
            }
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
                ready_queues_[0].addProcess(i);
            }
        }
    }

    void SimulationEngine::selectionPhase() {
        if (running_ != -1) {
            return;
        }
        for (size_t i = 0; i < ready_queues_.size(); ++i) {
            if (!ready_queues_[i].isEmpty()) {
                running_ = ready_queues_[i].getNextProcess();
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
        } else if (processes_[running_].quantumUsed() >= ready_queues_[processes_[running_].currentQueue()].getTimeQuantum()) {
            int current_queue = processes_[running_].currentQueue();
            if (current_queue < static_cast<int>(ready_queues_.size()) - 1) {
                processes_[running_].changeQueue(current_queue + 1);
            }
            ready_queues_[processes_[running_].currentQueue()].addProcess(running_);
            running_ = -1;
        }
    }

    void SimulationEngine::priorityBoostPhase() {
        if (current_tick_ > 0 && current_tick_ % config_.boost_interval == 0){
            for (size_t i = 1; i < ready_queues_.size(); ++i) {
                while (!ready_queues_[i].isEmpty()) {
                    int idx = ready_queues_[i].getNextProcess();
                    processes_[idx].changeQueue(0);
                    ready_queues_[0].addProcess(idx);
                    processes_[idx].resetQuantum();
                    }
                }
        }
    }