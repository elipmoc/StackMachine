#pragma once
template<typename AD>
struct JMP :OrderBase
{
private:
	AD ad;
	StackMachine& sm;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<1>>()
	{
		*sm.GetPR()= *(char**)(ad.GetAdr<1>())-4;
	};
	template<>
	void Do2<Args<2>>()
	{
		*sm.GetPR() = *(char**)(ad.GetAdr<1>()+*(int*)ad.GetAdr<2>())-4;
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	JMP(AD ad,StackMachine& sm) :ad(ad),sm(sm) {}
};

template<typename AD>
auto MakeJMP(AD ad, StackMachine& sm) {
	return new JMP<AD>(ad, sm);
}