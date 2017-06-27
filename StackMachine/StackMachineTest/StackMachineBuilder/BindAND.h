#pragma once
template<typename type>
struct BindAND :boost::static_visitor<OrderBase*> {
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<2> args)const {
		return MakeAND(type(), args);
	}
	template<>
	OrderBase* operator ()(Args<3> args)const {
		return MakeAND(type(), args);
	}
	template<>
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