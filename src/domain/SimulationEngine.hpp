#pragma once
#include <vector>
#include "Process.hpp"
#include "IResultsExporter.hpp"
#include "ISchedulingPolicy.hpp"


class SimulationEngine{
    public:
        SimulationEngine(std::vector<Process>& processes, IResultsExporter& results_exporter, ISchedulingPolicy& scheduling_policy);
        void run();
    
    private:

        void arrivalPhase();

        void markFirstResponsePhase();

        void consumeTickPhase();

        void checkCompletionTickPhase();

        std::vector<Process> processes_;
        int current_tick_ = 0;
        int running_ = -1;
        size_t finished_count_ = 0;                         
        IResultsExporter& results_exporter_;
        ISchedulingPolicy& scheduling_policy_;
};