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
		std::cout<<*(type*)ad.adr1<<std::endl;
	};
	template<>
	void Do2<Args<6>>()
	{
		std::cout << *(type*)(ad.adr1 + *ad.x1) << std::cout;
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	PRINT(AD ad) :ad(ad) {}
};

template<typename Type>
struct MakePRINT {
	template<typename AD>
	auto operator()(AD ad) {
		return new PRINT<Type, AD>(ad);
	}
};