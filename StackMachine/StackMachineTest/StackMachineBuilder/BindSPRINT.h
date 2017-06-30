#pragma once
struct BindSPRINT :boost::static_visitor<OrderBase*> {
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<1> args)const {
		return MakeSPRINT(args);
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeSPRINT(args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindSPRINT(), va);
	}
	static auto Make() {
		return phx::bind(&BindSPRINT::_Make, spt::_1);
	}
};