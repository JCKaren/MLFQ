#pragma once
#include <stdexcept>

class Process{
    public: 
    Process(int pid, int arrival_time, int burst_time);

    void consumeTick(){
        remaining_time_--;
        quantum_used_++;
    }

    void firstExecution(int current_tick){
        first_response_time_ = current_tick;
        start_time_ = current_tick;
    }

    void finishProcess(int current_tick){
        finish_time_ = current_tick;
    }
    
    void changeQueue(int new_queue_id){
        current_queue_ = new_queue_id;
    }

    void resetQuantum(){
        quantum_used_ = 0;
    }

    bool isFinished () const{
        return remaining_time_ == 0;
    }

    bool hasResponded () const{
        return first_response_time_ !=NOT_SET;
    }

    int quantumUsed () const{
        return quantum_used_;
    }

    int responseTime() const{
        return first_response_time_ - arrival_time_;
    }

    int turnaroundTime() const{
        return finish_time_ - arrival_time_;
    }

    int waitingTime() const{
        return turnaroundTime() - burst_time_;
    }

    int pid() const {return pid_;}

    int arrivalTime() const {return arrival_time_;}

    int burstTime() const {return burst_time_;}

    int remainingTime() const {return remaining_time_;}

    int currentQueue() const {return current_queue_;}

    int startTime() const { return start_time_; }

    int finishTime() const { return finish_time_; }


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
        static constexpr int NOT_SET = -1;
};


