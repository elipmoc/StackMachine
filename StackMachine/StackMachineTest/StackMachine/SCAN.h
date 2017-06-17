#pragma once
template<typename type, typename AD>
struct SCAN :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<1>>()
	{
		std::cin>> *(type*)ad.GetAdr<1>();
	};
	template<>
	void Do2<Args<2>>()
	{
		std::cin >> *(type*)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>());
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	SCAN(AD ad) :ad(ad) {}
};

template<typename Type, typename AD>
auto MakeSCAN(Type, AD ad) {
	return new SCAN<Type, AD>(ad);
}