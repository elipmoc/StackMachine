#pragma once
template<typename type>
struct BindMOD :boost::static_visitor<OrderBase*> {
	OrderBase* operator ()(...)const {
		throw std::string("errorArgs");
	}
	OrderBase* operator ()(Args<2> args)const {
		return MakeMOD(type(), args);
	}
	OrderBase* operator ()(Args<3> args)const {
		return MakeMOD(type(), args);
	}
	OrderBase* operator ()(Args<4> args)const {
		return MakeMOD(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindMOD(), va);
	}
	static auto Make() {
		return phx::bind(&BindMOD::_Make, spt::_1);
	}
};