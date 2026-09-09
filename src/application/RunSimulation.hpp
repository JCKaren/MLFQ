#pragma once
#include "../domain/SimulationEngine.hpp"
#include "../domain/MetricsCalculator.hpp"
#include "../domain/IAggregateExporter.hpp"


class RunSimulation {
public:
    RunSimulation(SimulationEngine& engine,
                  std::vector<Process>& processes,
                  MetricsCalculator& calculator,
                  IAggregateExporter& aggregateExporter);
    void execute();

private:
    SimulationEngine& engine_;
    std::vector<Process>& processes_;
    MetricsCalculator& calculator_;
    IAggregateExporter& aggregate_exporter_;
};

