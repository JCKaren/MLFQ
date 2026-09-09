$sources = @(
    "src/Main.cpp"
    "src/application/RunSimulation.cpp"
    "src/domain/metrics/MetricsCalculator.cpp"
    "src/domain/process/Process.cpp"
    "src/domain/scheduling/MlfqPolicy.cpp"
    "src/domain/scheduling/ReadyQueue.cpp"
    "src/domain/simulation/SimulationEngine.cpp"
    "src/infrastructure/CsvAggregateWriter.cpp"
    "src/infrastructure/CsvResultsWriter.cpp"
)

g++ -std=c++17 -Wall -Wextra -o test.exe $sources

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilacion exitosa" -ForegroundColor Green
} else {
    Write-Host "Error de compilacion" -ForegroundColor Red
}