#pragma once
#include <vector>
#include "Process.hpp"
#include "IResultsExporter.hpp"
#include "SimulationConfig.hpp"
#include "ReadyQueue.hpp"


class SimulationEngine{
    public:
        SimulationEngine(std::vector<Process> processes, IResultsExporter& results_exporter, SimulationConfig config);
        void run();
    
    private:

        void arrivalPhase();

        void selectionPhase();

        void markFirstResponsePhase();

        void consumeTickPhase();

        void checkCompletionTickPhase();

        void priorityBoostPhase();

        std::vector<Process> processes_;
        std::vector<ReadyQueue> ready_queues_;
        int current_tick_ = 0;
        int running_ = -1;
        size_t finished_count_ = 0;                         
        IResultsExporter& results_exporter_;
        SimulationConfig config_;
};