#pragma once
template<typename type>
struct BindPUSH :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
public: BindPUSH(StackMachine* sm) :sm(sm) {}
		template<class Args>
		OrderBase* operator ()(Args)const { throw "errorArgs"; };
		template<>
		OrderBase* operator ()(Args<1> args)const {
			return MakePUSH(type(), args, *sm);
		}
		template<>
		OrderBase* operator ()(Args<2> args)const {
			return MakePUSH(type(), args, *sm);
		}

		static OrderBase* _Make(StackMachine* sm, VarArgs& va) {
			return boost::apply_visitor(BindPUSH<type>(sm), va);
		}
		static auto Make(StackMachine& sm) {
			return phx::bind(&BindPUSH::_Make, &sm, spt::_1);
		}
};