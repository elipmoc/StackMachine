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
	void Do2<Args<1>>()
	{
		*(bool*)sm.GetAX() = (*(type*)ad.adr1) != (*(type*)ad.adr2);
	};
	template<>
	void Do2<Args<2>>()
	{
		*(bool*)sm.GetAX() = *(type*)(ad.adr1 + *ad.x1) != *(type*)ad.adr2;
	};
	template<>
	void Do2<Args<3>>()
	{
		*(bool*)sm.GetAX() = *(type*)ad.adr1 != *(type*)(ad.adr2 + *ad.x2);
	};
	template<>
	void Do2<Args<4>>()
	{
		*(bool*)sm.GetAX() = *(type*)(ad.adr1 + *ad.x1) != *(type*)(ad.adr2 + *ad.x2);
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
