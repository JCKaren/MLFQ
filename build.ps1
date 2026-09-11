$applicationSources = @(
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

$testSources = @(
    "test/unit/TestMain.cpp"
    "test/unit/ProcessTest.cpp"
    "test/unit/MlfqTest.cpp"
    "test/unit/MetricsTest.cpp"
    "test/unit/SimulationEngineTest.cpp"
    "src/domain/metrics/MetricsCalculator.cpp"
    "src/domain/process/Process.cpp"
    "src/domain/scheduling/MlfqPolicy.cpp"
    "src/domain/scheduling/ReadyQueue.cpp"
    "src/domain/simulation/SimulationEngine.cpp"
)

g++ -std=c++17 -Wall -Wextra -pedantic $applicationSources -o app.exe

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilacion de la aplicacion exitosa" -ForegroundColor Green
    .\app.exe
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Error al ejecutar la aplicacion" -ForegroundColor Red
        exit 1
    }
    Write-Host "Resultados generados en results.csv y aggregate.csv" -ForegroundColor Green
} else {
    Write-Host "Error de compilacion de la aplicacion" -ForegroundColor Red
    exit 1
}

g++ -std=c++17 -Wall -Wextra -pedantic $testSources -Isrc -o test.exe

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilacion de pruebas exitosa" -ForegroundColor Green
    .\test.exe
    exit $LASTEXITCODE
} else {
    Write-Host "Error de compilacion de pruebas" -ForegroundColor Red
    exit 1
}