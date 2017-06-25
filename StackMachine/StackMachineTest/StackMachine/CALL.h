#pragma once
template<typename AD>
struct CALL:OrderBase
{
private:
	AD ad;
	StackMachine& sm;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<1>>()
	{
		**(void***)sm.GetSP() = *(void**)sm.GetPR();
		*(char**)sm.GetSP() += sizeof(void*);
		*sm.GetPR() = *(char**)(ad.GetAdr<1>());
	};
	template<>
	void Do2<Args<2>>()
	{
		**(void***)sm.GetSP() = *(void**)sm.GetPR();
		*(char**)sm.GetSP() += sizeof(void*);
		*sm.GetPR() = *(char**)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>());
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	CALL(AD ad, StackMachine& sm) :ad(ad), sm(sm) {}
};

template<typename AD>
auto MakeCALL(AD ad, StackMachine& sm) {
	return new CALL<AD>(ad, sm);
}