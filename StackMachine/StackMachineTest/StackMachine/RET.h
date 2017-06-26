#pragma once

struct RET :OrderBase
{
private:
	StackMachine& sm;
public:
	virtual void Do() {
		*(char**)sm.GetSP() -= sizeof(void*);
		*sm.GetPR() = **(char***)sm.GetSP();
	};
	RET(StackMachine& sm) :sm(sm) {}
};

inline auto MakeRET(StackMachine& sm) {
	return new RET(sm);
}