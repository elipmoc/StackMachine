#pragma once

struct BindDCV {
	StackMachine* sm;
	std::string label;
	BindDCV(StackMachine* sm,std::string label) :sm(sm),label(label){}
	template<class T>
	void operator ()(T t)const{
		sm->DCV(t, label);
	}
	template< typename T>
	static void _Make(StackMachine* sm,std::string label,std::vector<T> v) {
		BindDCV(sm,label)(v);
	}
	template< typename T>
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindDCV::_Make<T>,&sm,spt::_1,spt::_2);
	}
};

struct BindLabelAdr
{
	static void* _Make(StackMachine* sm, std::string label) {
		return (*sm)[label];
	}
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindLabelAdr::_Make, &sm, spt::_1);
	}
};

struct BindValueAdr :boost::static_visitor<void*>
{
	StackMachine* sm;
	BindValueAdr(StackMachine* sm) :sm(sm){}
	template<class T>
	void* operator ()(T t)const {
		return sm->ValueLabel(t);
	}
	static void* _Make(StackMachine* sm,VarValue& vv ) {
		return boost::apply_visitor(BindValueAdr(sm),vv);
	}
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindValueAdr::_Make, &sm, spt::_1);
	}
};

template<typename type>
struct BindPRINT :boost::static_visitor<OrderBase*> {
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<5> args)const {
		return MakePRINT(type(), args);
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakePRINT(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindPRINT(),va);
	}
	static auto Make() {
		return phx::bind(&BindPRINT::_Make,spt::_1);
	}
};

template<typename type>
struct BindLD :boost::static_visitor<OrderBase*> {
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakeLD(type(), args);
	}
	template<>
	OrderBase* operator ()(Args<3> args)const {
		return MakeLD(type(), args);
	}
	template<>
	OrderBase* operator ()(Args<4> args)const {
		return MakeLD(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindLD(), va);
	}
	static auto Make() {
		return phx::bind(&BindLD::_Make, spt::_1);
	}
};

template<typename type>
struct BindADD :boost::static_visitor<OrderBase*> {
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakeADD(type(), args);
	}
	template<>
	OrderBase* operator ()(Args<3> args)const {
		return MakeADD(type(), args);
	}
	template<>
	OrderBase* operator ()(Args<4> args)const {
		return MakeADD(type(), args);
	}

	static OrderBase* _Make(VarArgs& va) {
		return boost::apply_visitor(BindADD(), va);
	}
	static auto Make() {
		return phx::bind(&BindADD::_Make, spt::_1);
	}
};

template<typename type>
struct BindCPA :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
	BindCPA(StackMachine* sm):sm(sm){}
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakeCPA(type(), args,*sm);
	}
	template<>
	OrderBase* operator ()(Args<3> args)const {
		return MakeCPA(type(), args,*sm);
	}
	template<>
	OrderBase* operator ()(Args<4> args)const {
		return MakeCPA(type(), args,*sm);
	}

	static OrderBase* _Make(StackMachine* sm,VarArgs& va) {
		return boost::apply_visitor(BindCPA(sm), va);
	}
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindCPA::_Make,&sm ,spt::_1);
	}
};

struct BindJMP :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
	BindJMP(StackMachine* sm):sm(sm){}
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakeJMP(args,*sm);
	}
	template<>
	OrderBase* operator ()(Args<5> args)const {
		return MakeJMP(args,*sm);
	}
	static OrderBase* _Make(StackMachine* sm,VarArgs& va) {
		return boost::apply_visitor(BindJMP(sm), va);
	}
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindJMP::_Make,&sm, spt::_1);
	}
};

struct BindJMPB :boost::static_visitor<OrderBase*> {
	StackMachine* sm;
	BindJMPB(StackMachine* sm) :sm(sm) {}
	template<class Args>
	OrderBase* operator ()(Args)const {
		return nullptr;
	}
	template<>
	OrderBase* operator ()(Args<1> args)const {
		return MakeJMPB(args, *sm);
	}
	template<>
	OrderBase* operator ()(Args<3> args)const {
		return MakeJMPB( args, *sm);
	}
	template<>
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

struct BindArgs1
{
	static Args<1> _Make(void* adr1,void* adr2) {
		return Args<1>(adr1, adr2);
	}
	static auto Make() {
		return phx::bind(&BindArgs1::_Make,spt::_1,spt::_2);
	}
};


struct BindArgs3
{
	static Args<3> _Make(void* adr1, void* adr2, void* x2) {
		return Args<3>(adr1, adr2,x2);
	}
	static auto Make() {
		return phx::bind(&BindArgs3::_Make, spt::_1, spt::_2, spt::_3);
	}
};

struct BindArgs4
{
	static Args<4> _Make(void* adr1,void* x1, void* adr2, void* x2) {
		return Args<4>(adr1,x1, adr2, x2);
	}
	static auto Make() {
		return phx::bind(&BindArgs4::_Make, spt::_1, spt::_2, spt::_3,spt::_4);
	}
};

struct BindArgs5
{
	static Args<5> _Make(void* adr1) {
		return Args<5>(adr1);
	}
	static auto Make() {
		return phx::bind(&BindArgs5::_Make, spt::_1);
	}
};
