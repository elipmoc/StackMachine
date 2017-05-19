#pragma once
struct BindJMP :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
	BindJMP(StackMachine* sm) :sm(sm) {}
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakeJMP(args, *sm);
	}
	template<>
	OrderBase* operator ()(Args<5> args)const {
		return MakeJMP(args, *sm);
	}
	static OrderBase* _Make(StackMachine* sm, VarArgs& va) {
		return boost::apply_visitor(BindJMP(sm), va);
	}
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindJMP::_Make, &sm, spt::_1);
	}
};
