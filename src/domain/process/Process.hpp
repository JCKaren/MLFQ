#pragma once
#include <stdexcept>
#include "ProcessMetrics.hpp"

class Process{
    public: 
    Process(int pid, int arrival_time, int burst_time);

    void consumeTick(); 

    void firstExecution(int current_tick);

    void finishProcess(int current_tick);
    
    void changeQueue(int new_queue_id);

    void resetQuantum();

    bool isFinished ();

    bool hasResponded ();

    int quantumUsed ();

    //Getters
    int pid() const {return pid_;}

    int currentQueue() const {return current_queue_;}

    int startTime() const { return start_time_; }

    int finishTime() const { return finish_time_; }

    int arrivalTime() const {return arrival_time_;}

    int burstTime() const {return burst_time_;}

    int remainingTime() const {return remaining_time_;}

    
    ProcessMetrics metrics() const;

    int responseTime() const;

    int turnaroundTime() const;

    int waitingTime() const;

    
    private:
        int pid_;
        int arrival_time_;
        int burst_time_;
        int remaining_time_;
        int start_time_;
        int finish_time_;
        int first_response_time_;
        int current_queue_;
        int quantum_used_;
        //Flag para determinar que un parámetro aún no esta definido
        //Se usa -1 dado a que un proceso puede iniciar en 0
        static constexpr int NOT_SET = -1;  
};


