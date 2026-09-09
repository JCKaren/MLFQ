#pragma once
#include "../domain/IAggregateExporter.hpp"
#include <string>


class CsvAggregateWriter : public IAggregateExporter {
    public:
        explicit CsvAggregateWriter(std::string path);
        void exportAggregate(const AggregateMetrics& metrics) override;
    private:
        std::string path_;
};