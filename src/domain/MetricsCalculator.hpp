#pragma once
#include "AggregateMetrics.hpp"
#include "ProcessMetrics.hpp"
#include <vector>

class MetricsCalculator {
    public:
        AggregateMetrics calculateAggregateMetrics
        (const std::vector<ProcessMetrics>& process_metrics) const;
};