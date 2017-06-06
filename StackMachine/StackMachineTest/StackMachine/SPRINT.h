#pragma once
template<typename AD>
struct SPRINT :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<1>>()
	{
		std::cout << ad.GetAdr<1>();
	};
	template<>
	void Do2<Args<2>>()
	{
		std::cout << (ad.GetAdr<1>() + *(int*)ad.GetAdr<2>());
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	SPRINT(AD ad) :ad(ad) {}
};

template<typename AD>
auto MakeSPRINT(AD ad) {
	return new SPRINT<AD>(ad);
}