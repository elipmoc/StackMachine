#pragma once
template<typename type,typename AD>
struct PUSH :OrderBase
{
private:
	AD ad;
	StackMachine& sm;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<1>>()
	{
		**(type**)sm.GetSP() = *(type*)(ad.GetAdr<1>());
		*(char**)sm.GetSP() += sizeof(type);

	};
	template<>
	void Do2<Args<2>>()
	{
		**(type**)sm.GetSP() = *(type*)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>());
		*(char**)sm.GetSP() += sizeof(type);
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	PUSH(AD ad, StackMachine& sm) :ad(ad), sm(sm) {}
};

template<typename type,typename AD>
auto MakePUSH(type,AD ad, StackMachine& sm) {
	return new PUSH<type,AD>(ad, sm);
}