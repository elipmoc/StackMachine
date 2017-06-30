#pragma once
template<typename type>
struct BindLDR :boost::static_visitor<OrderBase*> {
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeLDR(type(), args);
	}
	OrderBase* operator ()(Args<3> args)const {
		return MakeLDR(type(), args);
	}
	OrderBase* operator ()(Args<4> args)const {
		return MakeLDR(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindLDR(), va);
	}
	static auto Make() {
		return phx::bind(&BindLDR::_Make, spt::_1);
	}
};