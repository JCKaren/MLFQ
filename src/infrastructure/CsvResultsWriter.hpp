#pragma once
#include <string>
#include "../domain/IResultsExporter.hpp"

class CsvResultsWriter : public IResultsExporter {
public:
    explicit CsvResultsWriter(std::string path);
    void exportResults(const std::vector<Process>& processes) override;
private:
    std::string path_;
};