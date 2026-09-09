#pragma once
#include "../domain/simulation/SimulationEngine.hpp"
#include "../domain/metrics/MetricsCalculator.hpp"
#include "../application/ports/IAggregateExporter.hpp"
#include "../application/ports/IResultsExporter.hpp"


class RunSimulation {
public:
    RunSimulation(SimulationEngine& engine,
                  std::vector<Process>& processes,
                  MetricsCalculator& calculator,
                  IResultsExporter& resultsExporter,
                  IAggregateExporter& aggregateExporter);
    void execute();

private:
    SimulationEngine& engine_;
    std::vector<Process>& processes_;
    MetricsCalculator& calculator_;
    IResultsExporter& results_exporter_;
    IAggregateExporter& aggregate_exporter_;
};

