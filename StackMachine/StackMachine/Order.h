#pragma once
#include "AddressType.h"
#include "AdressData.h"

struct OrderBase
{
	virtual void Do()=0;
};

template<typename type,typename AD>
struct LD :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<AdressData<1>>() { *(type*)ad.adr1 = *(type*)ad.adr2; };
	template<>
	void Do2<AdressData<2>>() { *(type*)(ad.adr1 + *ad.x1) = *(type*)ad.adr2; };
public:
	virtual void Do() {
		Do2<AD>();
	};
	LD(AD ad) {
		this->ad = ad;
	}
};

template<typename Type>
struct MakeLD {
	template<typename AD>
	static auto Make(AD ad) {
		return new LD<Type, AD>(ad);
	}
};
