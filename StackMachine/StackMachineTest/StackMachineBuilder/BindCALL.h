#pragma once

struct BindCALL :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
public:
	BindCALL(StackMachine* sm) :sm(sm) {}
	template<class Args>
	OrderBase* operator ()(Args)const { throw std::string("errorArgs"); };
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakeCALL(args, *sm);
	}
	template<>
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