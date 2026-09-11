#pragma once
#include <string>

extern int failures;
void check(bool condition, const std::string& name);
void runProcessTest();
void runMlfqPolicyTest();
void runMetricsCalculatorTest();
void runSimulationEngineTest();