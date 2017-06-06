#pragma once
template<typename type, typename AD>
struct DREF :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<2>>()
	{
		(*(type*)ad.GetAdr<1>()) = **(type**)ad.GetAdr<2>();
	};
	template<>
	void Do2<Args<3>>()
	{
		*(type*)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>()) = **(type**)ad.GetAdr<3>();
	};
	template<>
	void Do2<Args<4>>()
	{
		*(type*)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>()) = **(type**)(ad.GetAdr<3>() + *(int*)ad.GetAdr<4>());
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	DREF(AD ad) :ad(ad) {}
};

template<typename type,typename AD>
auto MakeDREF(type,AD ad) {
	return new DREF<type, AD>(ad);
}
