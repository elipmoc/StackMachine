#pragma once
template<typename type, typename AD>
struct PRINT :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<5>>()
	{
		std::cout<<*(type*)ad.adr1;
	};
	template<>
	void Do2<Args<1>>()
	{
		std::cout << *(type*)(ad.adr1 + *(int*)ad.adr2);
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	PRINT(AD ad) :ad(ad) {}
};

template<typename Type,typename AD>
auto MakePRINT(Type, AD ad) {
	return new PRINT<Type, AD>(ad);
}