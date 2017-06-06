#pragma once
struct BindArgs1
{
	static auto _Make(void* adr1) {
		return Make_Arags( adr1 );
	}
	static auto Make() {
		return phx::bind(&BindArgs1::_Make, spt::_1);
	}
};


struct BindArgs2
{
	static auto _Make(void* adr1,void* adr2) {
		return Make_Arags(adr1,adr2);
	}
	static auto Make() {
		return phx::bind(&BindArgs2::_Make, spt::_1,spt::_2);
	}
};


struct BindArgs3
{
	static auto _Make(void* adr1, void* adr2, void* adr3) {
		return Make_Arags( adr1, adr2, adr3 );
	}
	static auto Make() {
		return phx::bind(&BindArgs3::_Make, spt::_1, spt::_2, spt::_3);
	}
};

struct BindArgs4
{
	static auto _Make(void* adr1, void* adr2, void* adr3, void* adr4) {
		return Make_Arags( adr1, adr2, adr3, adr4 );
	}
	static auto Make() {
		return phx::bind(&BindArgs4::_Make, spt::_1, spt::_2, spt::_3, spt::_4);
	}
};

