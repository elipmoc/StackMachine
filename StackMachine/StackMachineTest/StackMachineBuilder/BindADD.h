#pragma once
template<typename type>
struct BindADD :boost::static_visitor<OrderBase*> {
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeADD(type(), args);
	}
	OrderBase* operator ()(Args<3> args)const {
		return MakeADD(type(), args);
	}
	OrderBase* operator ()(Args<4> args)const {
		return MakeADD(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindADD(), va);
	}
	static auto Make() {
		return phx::bind(&BindADD::_Make, spt::_1);
	}
};