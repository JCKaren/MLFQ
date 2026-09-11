#include <stdexcept>
#include "ReadyQueue.hpp"

/*Clase para definir internamente los metodos usados por las colas*/
ReadyQueue::ReadyQueue(int time_quantum) : time_quantum_(time_quantum) {
    
}

void ReadyQueue::addProcess(int process_id) {
    process_queue_.push(process_id);
}

/*Cuando se selecciona un nuevo proceso, se guarda el id y se elimina de la cola de procesos
dado que ya va a hacer parte de la cola de ejecución*/
int ReadyQueue::getNextProcess() {
    if (process_queue_.empty()) {
        throw std::runtime_error("No hay procesos en la cola");
    }
    int next_process = process_queue_.front();
    process_queue_.pop();
    return next_process;
}

bool ReadyQueue::isEmpty() const {
    return process_queue_.empty();
}

int ReadyQueue::getTimeQuantum() const {
    return time_quantum_;
}
