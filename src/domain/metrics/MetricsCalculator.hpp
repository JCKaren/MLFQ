#pragma once
#include "AggregateMetrics.hpp"
#include "../process/ProcessMetrics.hpp"
#include <vector>

class MetricsCalculator {
    public:
        AggregateMetrics calculateAggregateMetrics
        (const std::vector<ProcessMetrics>& process_metrics) const;
};