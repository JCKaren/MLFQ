#pragma once
#include <vector>
#include "Process.hpp"


class ISchedulingPolicy {
    public:
        virtual ~ISchedulingPolicy() = default;
        virtual int getNextProcess() = 0;
        virtual void onProcessArrival(int process_index) = 0;
        virtual void onTick(int current_tick) = 0;
        virtual void onQuantumExpired(int process_index) = 0;
        virtual bool shouldPreempt(int process_index) const = 0;
};