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

    SimulationConfig config;
    config.quantums = {2, 4, 8};
    config.boost_interval = 20;

    CsvResultsWriter writer("results.csv");
    SimulationEngine engine(processes, writer, config);
    engine.run();

    return 0;

}