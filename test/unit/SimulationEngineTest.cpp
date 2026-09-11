#include "TestHelper.hpp"
#include "domain/simulation/SimulationEngine.hpp"
#include "domain/scheduling/MlfqPolicy.hpp"

void runSimulationEngineTest() {
	std::vector<Process> processes = {
		Process(1, 0, 3)
	};
	SimulationConfig config{{2, 4}, 10};
	MlfqPolicy policy(processes, config);
	SimulationEngine engine(processes, policy);

	engine.run();

	check(processes[0].startTime() == 0, "el motor registra el inicio del proceso");
	check(processes[0].finishTime() == 3, "el motor registra la finalizacion del proceso");
	check(processes[0].metrics().turnaround_time == 3, "el motor produce el turnaround correcto");

}