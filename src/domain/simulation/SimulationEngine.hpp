#pragma once
#include <vector>
#include "../process/Process.hpp"
#include "../scheduling/ISchedulingPolicy.hpp"

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
        /*Tiempo discreto, se define por ticks*/
        int current_tick_ = 0;
        /*-1 para CPU libre. 0 o > para indicar el indice del proceso siendo ejecutado*/
        int running_process_index_ = ISchedulingPolicy::NO_PROCESS;
        size_t finished_count_ = 0;                         
        ISchedulingPolicy& scheduling_policy_;
};