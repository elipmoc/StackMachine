#pragma once
template<typename type>
struct BindDIV :boost::static_visitor<OrderBase*> {
	template<class Args>
	OrderBase* operator ()(Args)const {
		throw std::string("errorArgs");
	}
	template<>
	OrderBase* operator ()(Args<2> args)const {
		return MakeDIV(type(), args);
	}
	template<>
	OrderBase* operator ()(Args<3> args)const {
		return MakeDIV(type(), args);
	}
	template<>
	OrderBase* operator ()(Args<4> args)const {
		return MakeDIV(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindDIV(), va);
	}
	static auto Make() {
		return phx::bind(&BindDIV::_Make, spt::_1);
	}
};