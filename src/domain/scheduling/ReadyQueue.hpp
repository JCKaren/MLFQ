#pragma once
#include <queue>

class ReadyQueue {
    public:
        explicit ReadyQueue(int time_quantum);

        void addProcess(int process_id);
        int getNextProcess();
        bool isEmpty() const;
        int getTimeQuantum() const;

    private:
        int time_quantum_;
        // Cada nivel usa FIFO para dar el mismo turno a los procesos que comparten prioridad
        std::queue<int> process_queue_;
};