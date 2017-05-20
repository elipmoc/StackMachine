#pragma once
template<typename AD>
struct REF :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<1>>()
	{
		(*(char**)ad.adr1) = ad.adr2;
	};
	template<>
	void Do2<Args<2>>()
	{
		*(char**)(ad.adr1 + *ad.x1) = ad.adr2;
	};
	template<>
	void Do2<Args<3>>()
	{
		*(char**)ad.adr1 = (ad.adr2 + *ad.x2);
	};
	template<>
	void Do2<Args<4>>()
	{
		*(char**)(ad.adr1 + *ad.x1) = (ad.adr2 + *ad.x2);
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
