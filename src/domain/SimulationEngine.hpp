#pragma once
#include <vector>
#include <deque>
#include "Process.hpp"
#include "IResultsExporter.hpp"


class SimulationEngine{
    public:
        SimulationEngine(std::vector<Process> processes, IResultsExporter& results_exporter);
        void run();
    
    private:

        void arrivalPhase();

        void selectionPhase();

        void markFirstResponsePhase();

        void consumeTickPhase();

        void checkCompletionTickPhase();

        void priorityBoostPhase();

        std::vector<Process> processes_;
        std::vector<std::deque<int>> queues_;
        int current_tick_ = 0;
        int running_ = -1;
        size_t finished_count_ = 0;
        const int quantums_[3] = {2, 4, 8};
        const int BOOST_INTERVAL = 20;
        IResultsExporter& results_exporter_;
};