#include "MetricsCalculator.hpp"
#include <stdexcept>

AggregateMetrics MetricsCalculator::calculateAggregateMetrics(const std::vector<ProcessMetrics>& process_metrics) const{
    
    if (process_metrics.empty()){
        throw std::runtime_error("No hay metricas en el vector");
    }

    int process_counter = static_cast<int>(process_metrics.size());
    double sum_response_time = 0; 
    double sum_turnaround_time = 0;
    double sum_waiting_time = 0;

    for (size_t i = 0; i < process_metrics.size(); i++){
        sum_response_time += process_metrics[i].response_time;
        sum_turnaround_time += process_metrics[i].turnaround_time;
        sum_waiting_time += process_metrics[i].waiting_time;
    } 
    return AggregateMetrics{sum_response_time/static_cast<double>(process_counter),
                            sum_turnaround_time/static_cast<double>(process_counter),
                            sum_waiting_time/static_cast<double>(process_counter),
                            process_counter};
}
