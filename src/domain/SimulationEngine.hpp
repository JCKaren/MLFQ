#pragma once
#include <vector>
#include "Process.hpp"
#include "ISchedulingPolicy.hpp"


class SimulationEngine{
    public:
        SimulationEngine(std::vector<Process>& processes, ISchedulingPolicy& scheduling_policy);
        void run();
    
    private:

        void arrivalPhase();

        void markFirstResponsePhase();

        void consumeTickPhase();

        void checkCompletionTickPhase();

        std::vector<Process>& processes_;
        int current_tick_ = 0;
        int running_ = -1;
        size_t finished_count_ = 0;                         
        ISchedulingPolicy& scheduling_policy_;
};