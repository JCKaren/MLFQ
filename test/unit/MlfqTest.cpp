#include "TestHelper.hpp"
#include "domain/scheduling/MlfqPolicy.hpp"

void runMlfqPolicyTest() {
	std::vector<Process> processes = {
		Process(1, 0, 5),
		Process(2, 0, 2)
	};
	SimulationConfig config{{2, 4}, 10};
	MlfqPolicy policy(processes, config);

	policy.onProcessArrival(0);
	policy.onProcessArrival(1);
	check(policy.getNextProcess() == 0, "MLFQ selecciona el proceso de la cola superior");

	policy.onQuantumExpired(0);
	check(processes[0].currentQueue() == 1, "MLFQ demueve al agotar el quantum");

	check(policy.getNextProcess() == 1, "MLFQ conserva el orden FIFO de la cola");

	policy.onTick(10, 0);
	check(processes[0].currentQueue() == 0, "MLFQ aplica boost al proceso en ejecucion");

}