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
