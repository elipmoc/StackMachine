#pragma once
struct BindREF :boost::static_visitor<OrderBase*> {
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<2> args)const {
		return MakeREF(args);
	}
	template<>
	OrderBase* operator ()(Args<3> args)const {
		return MakeREF(args);
	}
	template<>
	OrderBase* operator ()(Args<4> args)const {
		return MakeREF(args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindREF(), va);
	}
	static auto Make() {
		return phx::bind(&BindREF::_Make, spt::_1);
	}
};