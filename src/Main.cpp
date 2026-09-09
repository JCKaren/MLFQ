#include <vector>
#include "domain/process/Process.hpp"
#include "domain/simulation/SimulationEngine.hpp"
#include "domain/scheduling/SimulationConfig.hpp"
#include "infrastructure/CsvResultsWriter.hpp"
#include "domain/scheduling/MlfqPolicy.hpp"
#include "domain/process/ProcessMetrics.hpp"
#include "domain/metrics/MetricsCalculator.hpp"
#include "infrastructure/CsvAggregateWriter.hpp"
#include "application/RunSimulation.hpp"

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

  MlfqPolicy policy(processes, config);
    CsvResultsWriter csv_writer("results.csv");
    SimulationEngine engine(processes, policy);
    MetricsCalculator calculator;
    CsvAggregateWriter aggregateWriter("aggregate.csv");

    RunSimulation simulation(engine, processes, calculator, csv_writer, aggregateWriter);
    simulation.execute();

    return 0;

}