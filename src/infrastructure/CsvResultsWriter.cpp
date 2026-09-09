#include <fstream>
#include "CsvResultsWriter.hpp"
#include <stdexcept>

CsvResultsWriter::CsvResultsWriter(std::string path)
    : path_(path)
{
}


void CsvResultsWriter::exportResults(const std::vector<Process>& processes)
{
    std::ofstream file(path_);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + path_);
    }

    file << "PID,Arrival,Burst,Start,Finish,Response,Turnaround,Waiting\n";
    for (const auto& process : processes) {
        ProcessMetrics processMetrics = process.metrics();
        file << process.pid() << ","
             << process.arrivalTime() << ","
             << process.burstTime() << ","
             << process.startTime() << ","
             << process.finishTime() << ","
             << processMetrics.response_time << ","
             << processMetrics.turnaround_time << ","
             << processMetrics.waiting_time << "\n";
    }
    file.close();
}
