#include "domain/Process.hpp"
#include "domain/SimulationEngine.hpp"
#include "infrastructure/CsvResultsWriter.hpp"
#include <iostream>
#include <vector>


int main() {
    std::vector<Process> processes = {
        Process(1, 0, 8),
        Process(2, 1, 4),
        Process(3, 2, 9),
        Process(4, 3, 5)
    };


    CsvResultsWriter writer("results.csv");
    SimulationEngine engine(processes, writer);
    engine.run();

    return 0;

}