#pragma once
template<typename type, typename AD>
struct CPANEQ :OrderBase
{
private:
	AD ad;
	StackMachine& sm;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<2>>()
	{
		*(bool*)sm.GetAX() = (*(type*)ad.GetAdr<1>()) != (*(type*)ad.GetAdr<2>());
	};
	template<>
	void Do2<Args<3>>()
	{
		*(bool*)sm.GetAX() = *(type*)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>()) != *(type*)ad.GetAdr<3>();
	};
	template<>
	void Do2<Args<4>>()
	{
		*(bool*)sm.GetAX() = *(type*)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>()) != *(type*)(ad.GetAdr<3>() + *(int*)ad.GetAdr<4>());
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	CPANEQ(AD ad, StackMachine& sm) :ad(ad), sm(sm) {}
};

template<typename Type, typename AD>
auto MakeCPANEQ(Type, AD ad, StackMachine& sm)
{
	return new CPANEQ<Type, AD>(ad, sm);
}
