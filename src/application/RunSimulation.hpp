#pragma once
#include "../domain/SimulationEngine.hpp"
#include "../domain/MetricsCalculator.hpp"
#include "../domain/IAggregateExporter.hpp"
#include "../domain/IResultsExporter.hpp"


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

