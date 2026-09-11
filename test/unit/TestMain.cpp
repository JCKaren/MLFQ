#include "TestHelper.hpp"
#include <iostream>

int failures = 0;

void check(bool condition, const std::string& name) {
    if (condition) {
        std::cout << "[OK] " << name << "\n";
    } else {
        std::cout << "[FAIL] " << name << "\n";
        failures++;
    }
}

int main() {
    runProcessTest();
    runMlfqPolicyTest();
    runMetricsCalculatorTest();
    runSimulationEngineTest();
    
    std::cout << "\nFallos: " << failures << "\n";
    return failures;
}