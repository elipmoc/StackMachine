#pragma once
template<typename type, typename AD>
struct POP :OrderBase
{
private:
	AD ad;
	StackMachine& sm;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<5>>()
	{
		*(char**)sm.GetSP() -= sizeof(type);
		 *(type*)(ad.adr1)= **(type**)sm.GetSP();

	};
	template<>
	void Do2<Args<1>>()
	{
		*(char**)sm.GetSP() -= sizeof(type);
		*(type*)(ad.adr1 + *(int*)ad.adr2)= **(type**)sm.GetSP() ;
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	POP(AD ad, StackMachine& sm) :ad(ad), sm(sm) {}
};

template<typename type,typename AD>
auto MakePOP(type ,AD ad, StackMachine& sm) {
	return new POP<type,AD>(ad, sm);
}