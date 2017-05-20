#pragma once
struct BindSPRINT :boost::static_visitor<OrderBase*> {
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<5> args)const {
		return MakeSPRINT(args);
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakeSPRINT(args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindSPRINT(), va);
	}
	static auto Make() {
		return phx::bind(&BindSPRINT::_Make, spt::_1);
	}
};