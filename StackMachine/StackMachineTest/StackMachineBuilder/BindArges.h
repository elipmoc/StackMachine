#pragma once
struct BindArgs1
{
	static Args<1> _Make(void* adr1, void* adr2) {
		return Args<1>(adr1, adr2);
	}
	static auto Make() {
		return phx::bind(&BindArgs1::_Make, spt::_1, spt::_2);
	}
};


struct BindArgs3
{
	static Args<3> _Make(void* adr1, void* adr2, void* x2) {
		return Args<3>(adr1, adr2, x2);
	}
	static auto Make() {
		return phx::bind(&BindArgs3::_Make, spt::_1, spt::_2, spt::_3);
	}
};

struct BindArgs4
{
	static Args<4> _Make(void* adr1, void* x1, void* adr2, void* x2) {
		return Args<4>(adr1, x1, adr2, x2);
	}
	static auto Make() {
		return phx::bind(&BindArgs4::_Make, spt::_1, spt::_2, spt::_3, spt::_4);
	}
};

struct BindArgs5
{
	static Args<5> _Make(void* adr1) {
		return Args<5>(adr1);
	}
	static auto Make() {
		return phx::bind(&BindArgs5::_Make, spt::_1);
	}
};
