#pragma once
template<typename type>
struct BindINC :boost::static_visitor<OrderBase*> {
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<1> args)const {
		return MakeINC(type(), args);
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeINC(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindINC(), va);
	}
	static auto Make() {
		return phx::bind(&BindINC::_Make, spt::_1);
	}
};