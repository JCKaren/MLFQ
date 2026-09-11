#include "TestHelper.hpp"
#include "domain/metrics/MetricsCalculator.hpp"

void runMetricsCalculatorTest() {
	MetricsCalculator calculator;
	std::vector<ProcessMetrics> metrics = {
		ProcessMetrics{1, 1, 5, 2},
		ProcessMetrics{2, 3, 7, 4}
	};

	AggregateMetrics aggregate = calculator.calculateAggregateMetrics(metrics);

	check(aggregate.average_response_time == 2.0, "calcula el promedio de response time");
	check(aggregate.average_turnaround_time == 6.0, "calcula el promedio de turnaround time");
	check(aggregate.average_waiting_time == 3.0, "calcula el promedio de waiting time");
	check(aggregate.total_processes == 2, "cuenta la cantidad de procesos");

}