#pragma once
#include <string>
#include "../application/ports/IAggregateExporter.hpp"

class CsvAggregateWriter : public IAggregateExporter {
    public:
        explicit CsvAggregateWriter(std::string path);
        void exportAggregate(const AggregateMetrics& metrics) override;
    private:
        std::string path_;
};