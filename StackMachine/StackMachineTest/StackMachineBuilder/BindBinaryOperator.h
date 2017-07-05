#pragma once

//一つ型指定を持つタイプの二項演算子を生成するときに使う
#define MakeBind_BinaryOperator(OperatorName) \
template<typename type>\
struct Bind##OperatorName :boost::static_visitor<OrderBase*> {\
	OrderBase* operator ()(...)const {\
		throw std::string("errorArgs");\
	}\
	OrderBase* operator ()(Args<2> args)const {\
		return Make##OperatorName(type(), args);\
	}\
	OrderBase* operator ()(Args<3> args)const {\
		return Make##OperatorName(type(), args);\
	}\
	OrderBase* operator ()(Args<4> args)const {\
		return Make##OperatorName(type(), args);\
	}\
	static OrderBase* _Make(VarArgs& va) {\
		return boost::apply_visitor(Bind##OperatorName(), va);\
	}\
	static auto Make() {\
		return phx::bind(&Bind##OperatorName::_Make, spt::_1);\
	}\
}

MakeBind_BinaryOperator(ADD);
MakeBind_BinaryOperator(AND);
MakeBind_BinaryOperator(DIV);
MakeBind_BinaryOperator(MOD);
MakeBind_BinaryOperator(MUL);
MakeBind_BinaryOperator(OR);
MakeBind_BinaryOperator(XOR);
MakeBind_BinaryOperator(DREF);
MakeBind_BinaryOperator(LD);
MakeBind_BinaryOperator(LDR);



