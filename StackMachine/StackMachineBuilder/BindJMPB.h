#pragma once
struct BindJMPB :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
	BindJMPB(StackMachine* sm) :sm(sm) {}
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakeJMPB(args, *sm);
	}
	template<>
	OrderBase* operator ()(Args<3> args)const {
		return MakeJMPB(args, *sm);
	}
	template<>
	OrderBase* operator ()(Args<4> args)const {
		return MakeJMPB(args, *sm);
	}

	static OrderBase* _Make(StackMachine* sm, VarArgs& va) {
		return boost::apply_visitor(BindJMPB(sm), va);
	}
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindJMPB::_Make, &sm, spt::_1);
	}
};