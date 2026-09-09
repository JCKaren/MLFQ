#include "RunSimulation.hpp"

RunSimulation::RunSimulation(SimulationEngine& engine, std::vector<Process>& processes,
                             MetricsCalculator& calculator, IResultsExporter& results_exporter,
                             IAggregateExporter& aggregate_exporter)
    : engine_(engine), processes_(processes),
      calculator_(calculator), results_exporter_(results_exporter),
      aggregate_exporter_(aggregate_exporter)
{
}

void RunSimulation::execute() {
    engine_.run();

    results_exporter_.exportResults(processes_);

    std::vector<ProcessMetrics> process_metrics;
    for (const auto& process : processes_) {
        process_metrics.push_back(process.metrics());
    }

    AggregateMetrics aggregate = calculator_.calculateAggregateMetrics(process_metrics);
    aggregate_exporter_.exportAggregate(aggregate);
}