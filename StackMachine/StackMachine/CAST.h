#pragma once
template<typename type1,typename type2, typename AD>
struct CAST :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<1>>()
	{
		(*(type1*)ad.adr1) = (type1)(*(type2*)ad.adr2);
	};
	template<>
	void Do2<Args<2>>()
	{
		*(type1*)(ad.adr1 + *ad.x1) = (type1)(*(type2*)ad.adr2);
	};
	template<>
	void Do2<Args<3>>()
	{
		*(type1*)ad.adr1 = (type1)(*(type2*)(ad.adr2 + *ad.x2));
	};
	template<>
	void Do2<Args<4>>()
	{
		*(type1*)(ad.adr1 + *ad.x1) = (type1)(*(type2*)(ad.adr2 + *ad.x2));
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	CAST(AD ad) :ad(ad) {}
};

template<typename Type1,typename Type2>
struct MakeCAST {
	template<typename AD>
	auto operator()(AD ad) {
		return new CAST<Type1,Type2, AD>(ad);
	}
};
