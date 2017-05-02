#pragma once
template<typename type,typename AD>
struct CPA :OrderBase
{
private:
	AD ad;
	StackMachine& sm;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<1>>()
	{
		*(bool*)sm.GetAX()=(*(type*)ad.adr1) == (*(type*)ad.adr2);
	};
	template<>
	void Do2<Args<2>>()
	{
		*(bool*)sm.GetAX()=*(type*)(ad.adr1 + *ad.x1) == *(type*)ad.adr2;
	};
	template<>
	void Do2<Args<3>>()
	{
		*(bool*)sm.GetAX() = *(type*)ad.adr1 == *(type*)(ad.adr2 + *ad.x2);
	};
	template<>
	void Do2<Args<4>>()
	{
		*(bool*)sm.GetAX() = *(type*)(ad.adr1 + *ad.x1) == *(type*)(ad.adr2 + *ad.x2);
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	CPA(AD ad, StackMachine& sm) :ad(ad), sm(sm) {}
};

template<typename type>
struct MakeCPA {
	template<typename AD>
	auto operator()(AD ad, StackMachine& sm) {
		return new CPA<type,AD>(ad, sm);
	}
};