#pragma once
#include <vector>
#include "../../domain/process/Process.hpp"

class IResultsExporter {
public:
    virtual ~IResultsExporter() = default;
    virtual void exportResults(const std::vector<Process>& processes) = 0;
};