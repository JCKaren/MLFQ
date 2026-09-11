#include "SimulationEngine.hpp"

/*processes y scheduling_policy pasan por referencia para garantizar los mismos datos, no una copia*/
SimulationEngine::SimulationEngine(std::vector<Process>& processes, ISchedulingPolicy& scheduling_policy)
        : processes_(processes), scheduling_policy_(scheduling_policy)
    {
    }

    void SimulationEngine::run() {
        while (finished_count_ < processes_.size()) {
            arrivalPhase();
            /*Se verifica si toca hacer boost y en caso de que la CPU este libre
            se mira dentro de los procesos en espera cual es el que tiene mas prioridad*/
            scheduling_policy_.onTick(current_tick_,  running_process_index_);
            if (running_process_index_ == ISchedulingPolicy::NO_PROCESS) {
               running_process_index_ = scheduling_policy_.getNextProcess();
            }

            if (running_process_index_ != ISchedulingPolicy::NO_PROCESS) {
                markFirstResponsePhase();
                consumeTickPhase();
            }

            current_tick_++;

            /*Verificar si el proceso ya termino*/
            if (running_process_index_ != ISchedulingPolicy::NO_PROCESS) {
                checkCompletionTickPhase();
            }
        }
    }

    /*Se verifica si un proceso tiene el tiempo de llegada en el tiempo actual y se agg a Q0*/
    void SimulationEngine::arrivalPhase(){
        for (size_t i = 0; i < processes_.size(); ++i) {
            if (processes_[i].arrivalTime() == current_tick_) {
                scheduling_policy_.onProcessArrival(static_cast<int>(i));
            }
        }
    }

    /*Si es la primera ejecución de garantiza de actualizar los parámetros de inicio*/
    void SimulationEngine::markFirstResponsePhase() {
        if (running_process_index_ != ISchedulingPolicy::NO_PROCESS 
            && !processes_[running_process_index_].hasResponded()) {
            processes_[running_process_index_].firstExecution(current_tick_);
        }
    }

    void SimulationEngine::consumeTickPhase(){
        processes_[running_process_index_].consumeTick();
    }

    void SimulationEngine::checkCompletionTickPhase() {
        /*Si ya se termino el burst, se termina el proceso, la CPU queda libre y se aumenta 
        la cantidad de procesos terminados*/
        if (processes_[running_process_index_].isFinished()) {
            processes_[running_process_index_].finishProcess(current_tick_);
            running_process_index_ = ISchedulingPolicy::NO_PROCESS;
            finished_count_++;
        /*Si se agoto el quantum, se baja de nivel y la CPU queda libre*/
        } else if (scheduling_policy_.shouldPreempt(running_process_index_)) {
            scheduling_policy_.onQuantumExpired(running_process_index_);
            running_process_index_ = ISchedulingPolicy::NO_PROCESS;
        }
    }
