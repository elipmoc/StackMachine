#pragma once
template<typename type>
struct BindSCAN :boost::static_visitor<OrderBase*> {
	template<class Args>
	OrderBase* operator ()(Args)const {
		throw std::string("errorArgs");
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakeSCAN(type(), args);
	}
	template<>
	OrderBase* operator ()(Args<2> args)const {
		return MakeSCAN(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindSCAN(), va);
	}
	static auto Make() {
		return phx::bind(&BindSCAN::_Make, spt::_1);
	}
};