#pragma once
struct BindJMPB :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
	BindJMPB(StackMachine* sm) :sm(sm) {}
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeJMPB(args, *sm);
	}
	OrderBase* operator ()(Args<3> args)const {
		return MakeJMPB(args, *sm);
	}
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