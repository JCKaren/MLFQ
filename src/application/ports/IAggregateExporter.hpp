#pragma once
#include "../../domain/metrics/AggregateMetrics.hpp"

class IAggregateExporter{
    public:
        virtual ~IAggregateExporter() = default;
        virtual void exportAggregate(const AggregateMetrics& metrics) = 0;
};