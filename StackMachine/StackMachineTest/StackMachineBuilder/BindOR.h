#pragma once
template<typename type>
struct BindOR :boost::static_visitor<OrderBase*> {
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeOR(type(), args);
	}
	OrderBase* operator ()(Args<3> args)const {
		return MakeOR(type(), args);
	}
	OrderBase* operator ()(Args<4> args)const {
		return MakeOR(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindOR(), va);
	}
	static auto Make() {
		return phx::bind(&BindOR::_Make, spt::_1);
	}
};