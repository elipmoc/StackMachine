#pragma once
template<typename AD>
struct Ref :OrderBase
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
	Ref(AD ad) :ad(ad) {}
};

struct MakeRef {
	template<typename AD>
	auto operator()(AD ad) {
		return new Ref< AD>(ad);
	}
};
