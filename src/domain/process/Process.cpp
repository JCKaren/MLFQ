#include "Process.hpp"

Process::Process(int pid, int arrival_time, int burst_time)
    : pid_(pid),
      arrival_time_(arrival_time),
      burst_time_(burst_time),
      remaining_time_(burst_time),
      start_time_(NOT_SET),
      finish_time_(NOT_SET),
      first_response_time_(NOT_SET),
      current_queue_(0),
      quantum_used_(0)
{
    if (burst_time <= 0) {
        throw std::invalid_argument("burst_time debe ser mayor que cero");
    }
    if (arrival_time_<0){
        throw std::invalid_argument("arrival time debe ser mayor o igual que cero");
    }
}

void Process::consumeTick(){
    remaining_time_--;
    quantum_used_++;
}

void Process::firstExecution(int current_tick){
    first_response_time_ = current_tick;
    start_time_ = current_tick;
}

void Process::finishProcess(int current_tick){
    finish_time_= current_tick;
}

void Process::changeQueue(int new_queue_id){
    current_queue_ = new_queue_id;
}

void Process::resetQuantum(){
    quantum_used_= 0;
}

bool Process::isFinished(){
    return remaining_time_ == 0;
}

bool Process::hasResponded(){
    return start_time_ != NOT_SET;
}

int Process::quantumUsed(){
    return quantum_used_;
}

int Process::responseTime() const {
    return first_response_time_ - arrival_time_;
}

int Process::turnaroundTime() const {
    return finish_time_ - arrival_time_;
}

int Process::waitingTime() const {
    return turnaroundTime() - burst_time_;

}

ProcessMetrics Process::metrics() const {
        if (finish_time_ == NOT_SET || first_response_time_ == NOT_SET) {
            throw std::runtime_error("El proceso no ha terminado o respondido aún");
        }
        return ProcessMetrics{
            pid_,
            responseTime(),
            turnaroundTime(),
            waitingTime()
        };
}