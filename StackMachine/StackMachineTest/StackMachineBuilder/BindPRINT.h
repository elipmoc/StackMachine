#pragma once
template<typename type>
struct BindPRINT :boost::static_visitor<OrderBase*> {
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakePRINT(type(), args);
	}
	template<>
	OrderBase* operator ()(Args<2> args)const {
		return MakePRINT(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindPRINT(), va);
	}
	static auto Make() {
		return phx::bind(&BindPRINT::_Make, spt::_1);
	}
};