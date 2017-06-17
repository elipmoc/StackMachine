#pragma once
template<typename type, typename AD>
struct ADD :OrderBase
{
private:
	
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<2>>()
	{
		(*(type*)ad.GetAdr<1>()) += (*(type*)ad.GetAdr<2>());
	};
	template<>
	void Do2<Args<3>>()
	{
		*(type*)ad.GetAdr<1>() += *(type*)(ad.GetAdr<2>() + *(int*)ad.GetAdr<3>());
	};
	template<>
	void Do2<Args<4>>()
	{
		*(type*)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>())+= *(type*)(ad.GetAdr<3>() + *(int*)ad.GetAdr<4>());
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	ADD(AD ad) :ad(ad) {}
};

template<typename AD>
struct ADD<char*,AD> :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<2>>()
	{
		(*(char**)ad.GetAdr<1>()) += (*(int*)ad.GetAdr<2>());
	};
	template<>
	void Do2<Args<3>>()
	{
		*(char**)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>()) += *(int*)ad.GetAdr<3>();
	};
	template<>
	void Do2<Args<4>>()
	{
		*(char**)(ad.GetAdr<1>() + *(int*)ad.GetAdr<2>()) += *(int*)(ad.GetAdr<3>() + *(int*)ad.GetAdr<4>());
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	ADD(AD ad) :ad(ad) {}
};

template<typename AD>
struct ADD<bool, AD> :OrderBase
{
public:
	virtual void Do(){};
	ADD(AD ad) { throw std::string("not expect ADD<bool>"); }
};

template<typename Type,typename AD>
auto MakeADD(Type, AD ad)
{
	return new ADD<Type, AD>(ad);
}
