#include <stdexcept>
#include "MlfqPolicy.hpp"
#include "SimulationConfig.hpp"
#include "ReadyQueue.hpp"

/* La politica tiene dos parametros, proceso que se comparte como referencia con el motor
para asegurar que se este manejando los mismos datos, mientras que config es una copia
del parametro inmutable */
MlfqPolicy::MlfqPolicy(std::vector<Process>& processes, SimulationConfig config)
    : processes_(processes), config_(config)
    {
    if (config_.quantums.empty()) {
        throw std::invalid_argument("La lista de quantums esta vacia");
    }
    
    if (config_.boost_interval <= 0){
        throw std::invalid_argument("No se definio el intervalo de boost");
    }
    
    for (int quantum : config_.quantums) {
        if (quantum <= 0) {
            throw std::invalid_argument("Quantum definidos deben ser mayores a 0");
        }
        queues_.emplace_back(quantum);
    }
}

/* Se devuelve el primer proceso en la primera cola que no esta vacia, indicando el proceso
que tiene la mayor prioridad para ejecutarse.*/
int MlfqPolicy::getNextProcess()  {

    for (size_t i = 0; i < queues_.size(); ++i) {
        if (!queues_[i].isEmpty()) {
            int process_index = queues_[i].getNextProcess();
            return process_index;
        }
    }
    return NO_PROCESS; 
}

void MlfqPolicy::onProcessArrival(int process_index) {
    moveToQueue(process_index, 0);
}

/* Metodo que permite cumplir la regla 5, en donde todos los procesos suben a 
la cola de más prioridad*/
void MlfqPolicy::onTick(int current_tick, int running_process_index) {
    if (current_tick > 0 && current_tick % config_.boost_interval == 0) {
        //Los procesos encolados simplemente se cambian de cola y se actualizan sus parámetros
        for (size_t i = 1; i < queues_.size(); ++i) {
            while (!queues_[i].isEmpty()) {
                int process_index = queues_[i].getNextProcess();
                moveToQueue(process_index, 0);
            }
        }
        //Como el proceso que esta siendo ejecutado fue removido de la cola dado a que 
        //esta siendo ejecutado por la CPU, por lo que debe manualmente cambiar sus parámetros
        if (running_process_index != NO_PROCESS) {
            processes_[running_process_index].changeQueue(0);
            processes_[running_process_index].resetQuantum();
        }
    } 
}

/*Cuando un proceso ya expiro el quantum de la cola sin que se termine, por lo que 
se cambia de nivel en la cola*/
void MlfqPolicy::onQuantumExpired(int process_index) {
    int current_queue = processes_[process_index].currentQueue();
    if (current_queue < static_cast<int>(queues_.size()) - 1) {
        moveToQueue(process_index, current_queue + 1);
    } else {
        moveToQueue(process_index, current_queue);
    }
}

/* Consulta booleana para determinar si un proceso ya agoto el quantum*/
bool MlfqPolicy::shouldPreempt(int process_index) const {
    int queue_index = processes_[process_index].currentQueue();
    int time_quantum = queues_[queue_index].getTimeQuantum();
    return processes_[process_index].quantumUsed() >= time_quantum;
}

/*Al cambiar a la cola, se cambia los parámetros en el proceso*/
void MlfqPolicy::moveToQueue(int process_index, int new_queue) {
    processes_[process_index].changeQueue(new_queue);
    processes_[process_index].resetQuantum();
    queues_[new_queue].addProcess(process_index);
}
