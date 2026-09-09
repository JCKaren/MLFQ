#include <fstream>
#include "CsvAggregateWriter.hpp"
#include <stdexcept>

CsvAggregateWriter::CsvAggregateWriter(std::string path)
    : path_(path)
{
}


void CsvAggregateWriter::exportAggregate(const AggregateMetrics& metrics)
{
    std::ofstream file(path_);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + path_);
    }

    file << "AverageResponseTime,AverageTurnaroundTime,AverageWaitingTime,TotalProcesses\n";
        file << metrics.average_response_time << ","
             << metrics.average_turnaround_time << ","
             << metrics.average_waiting_time << ","
             << metrics.total_processes << "\n";
    file.close();
}
