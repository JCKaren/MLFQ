$sources = @(
    "src/Main.cpp"
    "src/application/RunSimulation.cpp"
    "src/domain/Process.cpp"
    "src/domain/SimulationEngine.cpp"
    "src/domain/ReadyQueue.cpp"
    "src/domain/MlfqPolicy.cpp"
    "src/domain/MetricsCalculator.cpp"
    "src/infrastructure/CsvResultsWriter.cpp"
    "src/infrastructure/CsvAggregateWriter.cpp"
)

g++ -std=c++17 -Wall -Wextra -o test.exe $sources

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilacion exitosa" -ForegroundColor Green
} else {
    Write-Host "Error de compilacion" -ForegroundColor Red
}