#pragma once
template<typename type1,typename type2, typename AD>
struct CAST :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<2>>()
	{
		(*(type1*)ad.GetAdr<1>()) = (type1)(*(type2*)ad.GetAdr<2>());
	};
	template<>
	void Do2<Args<3>>()
	{
		*(type1*)ad.GetAdr<1>() = (type1)(*(type2*)(ad.GetAdr<2>() + *(int*)ad.GetAdr<3>()));
	};
	template<>
	void Do2<Args<4>>()
	{
		*(type1*)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>()) = (type1)(*(type2*)(ad.GetAdr<3>() + *(int*)ad.GetAdr<4>()));
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	CAST(AD ad) :ad(ad) {}
};

template<typename Type1,typename Type2, typename AD>
auto MakeCAST(Type1, Type2, AD ad) {
	return new CAST<Type1, Type2, AD>(ad);
}

