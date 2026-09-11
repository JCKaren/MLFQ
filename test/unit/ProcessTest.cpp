#include "TestHelper.hpp"
#include "domain/process/Process.hpp"

static void consumeTicks(Process& process, int count) {
    for (int i = 0; i < count; ++i) {
        process.consumeTick();
    }
}

void runProcessTest() {
    {
        Process process(1, 0, 8);
        process.consumeTick();
        check(process.remainingTime() == 7, "consumeTick reduce el remaining");
    }
    {
        Process process(1, 0, 8);
        consumeTicks(process, 5);
        check(process.quantumUsed() == 5, "consumeTick aumenta el quantumUsed");
    }
    {
        Process process(1, 0, 8);
        consumeTicks(process, 5);
        process.resetQuantum();
        check(process.quantumUsed() == 0, "resetQuantum reinicia el quantumUsed");
    }
    {
        Process process(1, 0, 8);
        check(process.remainingTime() == 8, "un proceso nuevo tiene remaining igual al burst");
    }
    {
        Process process(1, 0, 3);
        check(!process.isFinished(), "un proceso nuevo no esta terminado");
        consumeTicks(process, 3);
        check(process.isFinished(), "el proceso termina al agotar su burst");
    }
    {
        Process process(1, 0, 3);
        check(!process.hasResponded(), "un proceso nuevo ha sido procesado");
        process.firstExecution(0);
        check(process.hasResponded(), "el proceso ha sido procesado");
    }
    {
        Process process(1, 0, 8);
        process.firstExecution(5);
        check(process.startTime() == 5, "el proceso ha sido iniciado en el tiempo 5");
    }
    {
        Process process(1, 0, 8);
        process.changeQueue(2);
        check(process.currentQueue() == 2, "el proceso ha sido movido a la cola 2");
    }
    {
        bool lanzo = false;
        try {
            Process process(1, 0, -5);
        } catch (const std::invalid_argument&) {
            lanzo = true;
        }
        check(lanzo, "burst negativo lanza excepcion");
    }
    {
        bool lanzo = false;
        try {
            Process process(1, -1, 3);
        } catch (const std::invalid_argument&) {
            lanzo = true;
        }
        check(lanzo, "arrival negativo lanza excepcion");
    }
    {
        bool lanzo = false;
        try {
            Process process(1, 0, 3);
            process.metrics();
        } catch (const std::runtime_error&) {
            lanzo = true;
        }
        check(lanzo, "el proceso no ha terminado por lo que las metricas no se han definido");
    }
    {
        Process process(1, 2, 4);
        process.firstExecution(5);
        for (size_t i = 0; i < 4; i++){
            process.consumeTick();
        }
        process.finishProcess(12);
        
        ProcessMetrics processMetrics = process.metrics();
        check(processMetrics.response_time == 3, "response = first_response - arrival");
        check(processMetrics.turnaround_time == 10, "response = first_response - arrival");
        check(processMetrics.waiting_time == 6, "response = first_response - arrival");
    }
}