#pragma once
namespace VirtualMachineBuilder {
	namespace phx = boost::phoenix;
	namespace spt = boost::spirit;
#include "BindBinaryOperator.h"
#include "BindNOT.h"
#include "BindINC.h"
#include "BindPOP.h"
#include "BindPUSH.h"
#include "BindJMP.h"
#include "BindJMPB.h"
#include "BindSCAN.h"
#include "BindPRINT.h"
#include "BindSPRINT.h"
#include "BindCPAEQ.h"
#include "BindCPANEQ.h"
#include "BindArges.h"
#include "BindREF.h"
#include "BindCAST.h"
#include "BindEND.h"
#include "BindCALL.h"
#include "BindRET.h"

	struct BindDCV {
		StackMachine* sm;
		std::string label;
		BindDCV(StackMachine* sm, std::string label) :sm(sm), label(label) {}
		template<class T>
		void operator ()(T t)const {
			sm->DCV(t, label);
		}
		template< typename T>
		static void _Make(StackMachine* sm, std::string label, std::vector<T> v) {
			BindDCV(sm, label)(v);
		}
		template< typename T>
		static auto Make(StackMachine& sm) {
			return phx::bind(&BindDCV::_Make<T>, &sm, spt::_1, spt::_2);
		}
	};

	template<class T>
	struct BindDS {
		StackMachine* sm;
		std::string label;
		BindDS(StackMachine* sm, std::string label) :sm(sm), label(label) {}
		void operator ()()const {
			sm->DS(sizeof(T), label);
		}
		template< typename T>
		static void _Make(StackMachine* sm, std::string label) {
			BindDS<T>(sm, label)();
		}
		template< typename T>
		static auto Make(StackMachine& sm) {
			return phx::bind(&BindDS::_Make<T>, &sm, spt::_1);
		}
	};

	struct BindDCVS {
		StackMachine* sm;
		std::string label;
		BindDCVS(StackMachine* sm, std::string label) :sm(sm), label(label) {}
		void operator ()(std::string str)const {
			std::vector<char> strv;
			for each (auto c in str)
			{
				strv.push_back(c);
			}
			sm->DCV(strv, label);
		}
		static void _Make(StackMachine* sm, std::string label, std::string str) {
			BindDCVS(sm, label)(str);
		}
		static auto Make(StackMachine& sm) {
			return phx::bind(&BindDCVS::_Make, &sm, spt::_1, spt::_2);
		}
	};

	struct BindLabelAdr
	{
		static void* _Make(StackMachine* sm, std::string label) {
			if (label[0] == '@' && !sm->ExistLabel(label))
				sm->DS(4, label);
			return (*sm)[label];
		}
		static auto Make(StackMachine& sm) {
			return phx::bind(&BindLabelAdr::_Make, &sm, spt::_1);
		}
	};

	struct BindValueAdr :boost::static_visitor<void*>
	{
		StackMachine* sm;
		BindValueAdr(StackMachine* sm) :sm(sm) {}
		template<class T>
		void* operator ()(T t)const {
			return sm->ValueLabel(t);
		}
		static void* _Make(StackMachine* sm, VarValue& vv) {
			return boost::apply_visitor(BindValueAdr(sm), vv);
		}
		static auto Make(StackMachine& sm) {
			return phx::bind(&BindValueAdr::_Make, &sm, spt::_1);
		}
	};
	struct BindStringAdr :boost::static_visitor<void*>
	{
		StackMachine* sm;
		BindStringAdr(StackMachine* sm) :sm(sm) {}
		void* operator ()(std::vector<char>& v)const {
			return sm->ValueLabel(v);
		}
		static void* _Make(StackMachine* sm, std::vector<char>& v) {
			return BindStringAdr(sm)(v);
		}
		static auto Make(StackMachine& sm) {
			return phx::bind(&BindStringAdr::_Make, &sm, spt::_1);
		}
	};

}