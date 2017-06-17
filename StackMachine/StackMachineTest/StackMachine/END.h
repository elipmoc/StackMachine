#pragma once
struct END :OrderBase
{
private:
	StackMachine& sm;
public:
	virtual void Do() {
		sm.SetEndFlag();
	};
	END(StackMachine& sm):sm(sm) {}
};

inline auto MakeEND(StackMachine& sm) {
	return new END(sm);
};
