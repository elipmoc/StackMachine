#pragma once


namespace VirtualMachine {
	class RunMachine;
}
namespace StackMachineBuilder {
	struct Script
	{
		Script();
		VirtualMachine::RunMachine CreateRunMachine();
		bool Parse(std::string::iterator& first, std::string::iterator& last);
	private:
		struct ImplScript;
		ImplScript* implScript;

	};

}