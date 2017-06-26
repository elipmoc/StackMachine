#pragma once
template<typename AD>
struct REF :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<2>>()
	{
		(*(char**)ad.GetAdr<1>()) = ad.GetAdr<2>();
	};
	template<>
	void Do2<Args<3>>()
	{
		*(char**)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>()) = ad.GetAdr<3>();
	};
	template<>
	void Do2<Args<4>>()
	{
		*(char**)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>()) = (ad.GetAdr<3>() + *(int*)ad.GetAdr<4>());
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	REF(AD ad) :ad(ad) {}
};

template<typename AD>
auto MakeREF(AD ad) {
	return new REF< AD>(ad);
}
