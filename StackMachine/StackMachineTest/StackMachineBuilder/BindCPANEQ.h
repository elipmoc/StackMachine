#pragma once
template<typename type>
struct BindCPANEQ :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
	BindCPANEQ(StackMachine* sm) :sm(sm) {}
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<2> args)const {
		return MakeCPANEQ(type(), args, *sm);
	}
	template<>
	OrderBase* operator ()(Args<3> args)const {
		return MakeCPANEQ(type(), args, *sm);
	}
	template<>
	OrderBase* operator ()(Args<4> args)const {
		return MakeCPANEQ(type(), args, *sm);
	}

	static OrderBase* _Make(StackMachine* sm, VarArgs& va) {
		return boost::apply_visitor(BindCPANEQ(sm), va);
	}
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindCPANEQ::_Make, &sm, spt::_1);
	}
};
