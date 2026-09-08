#pragma once
#include <queue>

class ReadyQueue {
    public:
        ReadyQueue(int priority_level, int time_quantum);

        void addProcess(int process_id);
        int getNextProcess();
        bool isEmpty() const;
        int getTimeQuantum() const;
        int getPriorityLevel() const;

    private:
        int priority_level_;
        int time_quantum_;
        std::queue<int> process_queue_;
};