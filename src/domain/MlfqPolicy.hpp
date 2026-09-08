#pragma once
#include "ISchedulingPolicy.hpp"
#include "SimulationConfig.hpp"
#include "ReadyQueue.hpp"

class MlfqPolicy : public ISchedulingPolicy {
    public:
        MlfqPolicy(std::vector<Process>& processes, SimulationConfig config);

        int getNextProcess() override;
        void onProcessArrival(int process_index) override;
        void onTick(int current_tick) override;
        void onQuantumExpired(int process_index) override;
        bool shouldPreempt(int process_index) const override;

    private:
        std::vector<Process>& processes_;
        std::vector<ReadyQueue> queues_;
        SimulationConfig config_;

        void moveToQueue(int process_index, int new_queue);
};