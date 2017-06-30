#pragma once
template<typename type>
struct BindAND :boost::static_visitor<OrderBase*> {
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeAND(type(), args);
	}
	OrderBase* operator ()(Args<3> args)const {
		return MakeAND(type(), args);
	}
	OrderBase* operator ()(Args<4> args)const {
		return MakeAND(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindAND(), va);
	}
	static auto Make() {
		return phx::bind(&BindAND::_Make, spt::_1);
	}
};