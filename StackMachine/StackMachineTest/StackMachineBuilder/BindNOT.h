#pragma once
template<typename type>
struct BindNOT :boost::static_visitor<OrderBase*> {
	template<class Args>
	OrderBase* operator ()(Args args)const {
		throw std::string("errorArgs");
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakeNOT(type(), args);
	}
	template<>
	OrderBase* operator ()(Args<2> args)const {
		return MakeNOT(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindNOT(), va);
	}
	static auto Make() {
		return phx::bind(&BindNOT::_Make, spt::_1);
	}
};