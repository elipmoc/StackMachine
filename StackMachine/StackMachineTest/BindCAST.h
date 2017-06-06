#pragma once
template<typename type1,typename type2>
struct BindCAST :boost::static_visitor<OrderBase*> {
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<2> args)const {
		return MakeCAST(type1(),type2(), args);
	}
	template<>
	OrderBase* operator ()(Args<3> args)const {
		return MakeCAST(type1(), type2(), args);
	}
	template<>
	OrderBase* operator ()(Args<4> args)const {
		return MakeCAST(type1(), type2(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindCAST(), va);
	}
	static auto Make() {
		return phx::bind(&BindCAST::_Make, spt::_1);
	}
};