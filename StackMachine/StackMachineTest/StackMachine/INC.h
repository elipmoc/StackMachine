template<typename type, typename AD>
struct INC :OrderBase
{
private:
	AD ad;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<5>>()
	{
		(*(type*)ad.adr1)++;
	};
	template<>
	void Do2<Args<1>>()
	{
		(*(type*)(ad.adr1 + *ad.adr2))++;
	};
	template<>
	void Do2<Args<6>>()
	{
		(*(type*)(ad.adr1 + *ad.x1))++;
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	INC(AD ad) :ad(ad) {}
};

template<typename Type,typename AD>
auto MakeINC(Type, AD ad) {
	return new INC<Type, AD>(ad);
};
