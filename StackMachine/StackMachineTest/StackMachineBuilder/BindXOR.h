#pragma once
template<typename type>
struct BindXOR :boost::static_visitor<OrderBase*> {
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeXOR(type(), args);
	}
	OrderBase* operator ()(Args<3> args)const {
		return MakeXOR(type(), args);
	}
	OrderBase* operator ()(Args<4> args)const {
		return MakeXOR(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindXOR(), va);
	}
	static auto Make() {
		return phx::bind(&BindXOR::_Make, spt::_1);
	}
};