#pragma once
template<typename AD>
struct JMPB :OrderBase
{
private:
	AD ad;
	StackMachine& sm;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<2>>()
	{
		if(*(bool*)ad.GetAdr<2>())
			*sm.GetPR() = *(char**)(ad.GetAdr<1>());
	};
	template<>
	void Do2<Args<3>>()
	{
		if (*(bool*)ad.GetAdr<3>())
			*sm.GetPR() = *(char**)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>());
	};
	template<>
	void Do2<Args<4>>()
	{
		if (*(bool*)(ad.GetAdr<3>()+*(int*)ad.GetAdr<4>()))
			*sm.GetPR() = *(char**)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>()) - 4;
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	JMPB(AD ad,StackMachine& sm) :ad(ad),sm(sm) {}
};
template<typename AD>
auto MakeJMPB(AD ad, StackMachine& sm) {
	return new JMPB< AD>(ad, sm);
}
