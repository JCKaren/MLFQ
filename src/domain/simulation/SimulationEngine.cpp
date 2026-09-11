#include "SimulationEngine.hpp"

SimulationEngine::SimulationEngine(std::vector<Process>& processes, ISchedulingPolicy& scheduling_policy)
        : processes_(processes), scheduling_policy_(scheduling_policy)
    {
    }

    void SimulationEngine::run() {
        while (finished_count_ < processes_.size()) {
            arrivalPhase();
            scheduling_policy_.onTick(current_tick_,  running_process_index_);
            if (running_process_index_ == ISchedulingPolicy::NO_PROCESS) {
               running_process_index_ = scheduling_policy_.getNextProcess();
            }
            if (running_process_index_ != ISchedulingPolicy::NO_PROCESS) {
                markFirstResponsePhase();
                consumeTickPhase();
            }

            current_tick_++;

            if (running_process_index_ != ISchedulingPolicy::NO_PROCESS) {
                checkCompletionTickPhase();
            }
        }
        
    }


    void SimulationEngine::arrivalPhase(){
        for (size_t i = 0; i < processes_.size(); ++i) {
            if (processes_[i].arrivalTime() == current_tick_) {
                scheduling_policy_.onProcessArrival(static_cast<int>(i));
            }
        }
    }

    void SimulationEngine::markFirstResponsePhase() {
        if (running_process_index_ != ISchedulingPolicy::NO_PROCESS 
            && !processes_[running_process_index_].hasResponded()) {
            processes_[running_process_index_].firstExecution(current_tick_);
        }
    }

    void SimulationEngine::consumeTickPhase(){
        processes_[running_process_index_].consumeTick();
    }

    void SimulationEngine::checkCompletionTickPhase() {
        if (processes_[running_process_index_].isFinished()) {
            processes_[running_process_index_].finishProcess(current_tick_);
            running_process_index_ = -1;
            finished_count_++;
        } else if (scheduling_policy_.shouldPreempt(running_process_index_)) {
            scheduling_policy_.onQuantumExpired(running_process_index_);
            running_process_index_ = -1;
        }
    }
