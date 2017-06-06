#pragma once
template<typename type>
struct BindCPAEQ :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
	BindCPAEQ(StackMachine* sm) :sm(sm) {}
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<2> args)const {
		return MakeCPAEQ(type(), args, *sm);
	}
	template<>
	OrderBase* operator ()(Args<3> args)const {
		return MakeCPAEQ(type(), args, *sm);
	}
	template<>
	OrderBase* operator ()(Args<4> args)const {
		return MakeCPAEQ(type(), args, *sm);
	}

	static OrderBase* _Make(StackMachine* sm, VarArgs& va) {
		return boost::apply_visitor(BindCPAEQ(sm), va);
	}
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindCPAEQ::_Make, &sm, spt::_1);
	}
};