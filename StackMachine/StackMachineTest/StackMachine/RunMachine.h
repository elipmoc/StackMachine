#pragma once
class RunMachine {
	StackMachine& sm;
public:
	RunMachine(StackMachine& sm) :sm(sm) {
	}
	void Run() {
		sm.Run();
	}
};