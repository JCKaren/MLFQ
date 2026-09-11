#pragma once
#include <vector>
#include "../process/Process.hpp"


class ISchedulingPolicy {
    public:
        virtual ~ISchedulingPolicy() = default;
        virtual int getNextProcess() = 0;
        virtual void onProcessArrival(int process_index) = 0;
        virtual void onTick(int current_tick, int running_index) = 0;
        virtual void onQuantumExpired(int process_index) = 0;
        virtual bool shouldPreempt(int process_index) const = 0;
        static constexpr int NO_PROCESS = -1;
};