#include "SimulationEngine.hpp"

SimulationEngine::SimulationEngine(std::vector<Process>& processes, IResultsExporter& results_exporter, ISchedulingPolicy& scheduling_policy)
        : processes_(processes), results_exporter_(results_exporter), scheduling_policy_(scheduling_policy)
    {
    }

    void SimulationEngine::run() {
        while (finished_count_ < processes_.size()) {
            arrivalPhase();
            scheduling_policy_.onTick(current_tick_);
            if (running_ == -1) {
               running_ = scheduling_policy_.getNextProcess();
            }
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
                scheduling_policy_.onProcessArrival(static_cast<int>(i));
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
        } else if (scheduling_policy_.shouldPreempt(running_)) {
            scheduling_policy_.onQuantumExpired(running_);
            running_ = -1;
        }
    }
