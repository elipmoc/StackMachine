#pragma once
template<typename type,typename AD>
struct DRef :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<1>>()
	{
		(*(type*)ad.adr1) = **(type**)ad.adr2;
	};
	template<>
	void Do2<Args<2>>()
	{
		*(type*)(ad.adr1 + *ad.x1) =**(type**)ad.adr2;
	};
	template<>
	void Do2<Args<3>>()
	{
		*(type*)ad.adr1 = **(type**)(ad.adr2 + *ad.x2);
	};
	template<>
	void Do2<Args<4>>()
	{
		*(type*)(ad.adr1 + *ad.x1) = **(type**)(ad.adr2 + *ad.x2);
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	DRef(AD ad) :ad(ad) {}
};

template<typename type>
struct MakeDRef {
	template<typename AD>
	auto operator()(AD ad) {
		return new DRef<type,AD>(ad);
	}
};
