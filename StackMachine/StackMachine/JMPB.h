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
	void Do2<Args<1>>()
	{
		if(*(bool*)ad.adr2)
			*sm.GetPR() = *(char**)(ad.adr1) - 4;
	};
	template<>
	void Do2<Args<2>>()
	{
		if (*(bool*)ad.adr2)
			*sm.GetPR() = *(char**)(ad.adr1 + *ad.x1) - 4;
	};
	template<>
	void Do2<Args<3>>()
	{
		if (*(bool*)(ad.adr2 + *ad.x2))
			*sm.GetPR() = *(char**)(ad.adr1) - 4;
	};
	template<>
	void Do2<Args<4>>()
	{
		if (*(bool*)(ad.adr2+*ad.x2))
			*sm.GetPR() = *(char**)(ad.adr1 + *ad.x1) - 4;
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
