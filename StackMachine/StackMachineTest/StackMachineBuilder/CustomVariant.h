#pragma once
namespace VirtualMachineBuilder {
	using namespace VirtualMachine;
	typedef boost::variant<int, double, bool, char> VarValue;
	typedef boost::variant<Args<1>, Args<2>, Args<3>, Args<4>> VarArgs;
}