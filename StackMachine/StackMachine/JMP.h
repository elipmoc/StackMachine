#pragma once
template<typename AD>
struct JMP :OrderBase
{
private:
	AD ad;
	StackMachine& sm;
	template<typename AD2>
	void Do2();
	template<>
	void Do2<Args<5>>()
	{
		*sm.GetPR()= *(char**)(ad.adr1)-4;
	};
	template<>
	void Do2<Args<6>>()
	{
		*sm.GetPR() = *(char**)(ad.adr1+*ad.x1)-4;
	};
public:
	virtual void Do() {
		Do2<AD>();
	};
	JMP(AD ad,StackMachine& sm) :ad(ad),sm(sm) {}
};


struct MakeJMP {
	template<typename AD>
	auto operator()(AD ad,StackMachine& sm) {
		return new JMP<AD>(ad,sm);
	}
};