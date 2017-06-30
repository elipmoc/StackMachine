#pragma once

struct BindCALL :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
public:
	BindCALL(StackMachine* sm) :sm(sm) {}
	OrderBase* operator ()(...)const { 
		throw std::string("errorArgs");
	};
	OrderBase* operator ()(Args<1> args)const {
		return MakeCALL(args, *sm);
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeCALL(args, *sm);
	}

	static OrderBase* _Make(StackMachine* sm, VarArgs& va) {
		return boost::apply_visitor(BindCALL(sm), va);
	}
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindCALL::_Make, &sm, spt::_1);
	}
};