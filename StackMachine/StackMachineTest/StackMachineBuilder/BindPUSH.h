#pragma once
template<typename type>
struct BindPUSH :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
public: BindPUSH(StackMachine* sm) :sm(sm) {}
		OrderBase* operator ()(...)const {
			throw std::string("errorArgs");
		};
		OrderBase* operator ()(Args<1> args)const {
			return MakePUSH(type(), args, *sm);
		}
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