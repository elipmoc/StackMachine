#pragma once
template<typename type>
struct BindLD :boost::static_visitor<OrderBase*> {
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeLD(type(), args);
	}
	OrderBase* operator ()(Args<3> args)const {
		return MakeLD(type(), args);
	}
	OrderBase* operator ()(Args<4> args)const {
		return MakeLD(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindLD(), va);
	}
	static auto Make() {
		return phx::bind(&BindLD::_Make, spt::_1);
	}
};