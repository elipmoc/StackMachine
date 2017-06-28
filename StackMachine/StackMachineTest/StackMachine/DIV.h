#pragma once
template<typename type, typename AD>
struct DIV :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<2>>()
	{
		(*(type*)ad.GetAdr<1>()) /= (*(type*)ad.GetAdr<2>());
	};
	template<>
	void Do2<Args<3>>()
	{
		*(type*)ad.GetAdr<1>() /= *(type*)(ad.GetAdr<2>() + *(int*)ad.GetAdr<3>());
	};
	template<>
	void Do2<Args<4>>()
	{
		*(type*)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>()) /= *(type*)(ad.GetAdr<3>() + *(int*)ad.GetAdr<4>());
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	DIV(AD ad) :ad(ad) {}
};

template<typename Type, typename AD>
auto MakeDIV(Type, AD ad)
{
	return new DIV<Type, AD>(ad);
}
