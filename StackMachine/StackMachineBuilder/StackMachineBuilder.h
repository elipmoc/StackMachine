#pragma once
#include "stdafx.h"
namespace phx = boost::phoenix;
namespace spt = boost::spirit;
#include "StackMachine.h"
#include "CustomVariant.h"
#include "BindOrder.h"


//グラマーの定義
/////////////////////////////////////////

template<typename Iterator>
struct Script :spt::qi::grammar<Iterator>{
private:
	StackMachine sm;
	OrderVector ov;
	auto AddOrder() {
		return phx::bind([this](OrderBase* ob) {ov << ob; }, spt::_1);
	}
	auto AddOrderLabel() {
		return phx::bind([this](std::string str) { ov << str; }, spt::_1);
	}
public:
	void Run() { sm.SetOrderVector(ov); sm.Run(); }
	Script() :Script::base_type(Code) {
		std::vector<int> v = {1,2,3};
		using boost::phoenix::ref;
		using spt::qi::eps;
		using spt::qi::lit;
		using spt::qi::_1;
		using spt::qi::_val;
		using spt::qi::double_;
		using spt::qi::bool_;
		using spt::qi::int_;
		using spt::qi::alpha;
		using spt::qi::as_string;
		using spt::ascii::char_;
		spt::qi::standard_wide::char_type wchar_;
		using spt::qi::real_parser;
		using spt::qi::strict_real_policies;
		real_parser<double, strict_real_policies<double>> strict_double;
		Code = 
			*(
				(DC >> lit(';')) 
				| 
				(-(Label[AddOrderLabel()]>>lit(' '))>>Order[AddOrder()] >> lit(';'))
				|
				(Comment)
			);
		NullChar = lit("\\0")[_val = '\0'];
		EndLineChar = lit("\\n")[_val='\n'];
		Char = lit('\'') >>(NullChar|EndLineChar|char_)-'\''>> lit('\'');
		Value = strict_double | int_|  Char|bool_;
		ValueAdr = Value[_val = BindValueAdr::Make(sm)] | String[_val=BindStringAdr::Make(sm)];
		DC =
			(Label >> lit(' ') >> lit("idc") >> lit(' ') >> int_%',')[BindDCV::Make<int>(sm)] |
			(Label >> lit(' ') >> lit("ddc") >> lit(' ') >> double_%',')[BindDCV::Make<double>(sm)] |
			(Label >> lit(' ') >> lit("bdc") >> lit(' ') >> bool_%',')[BindDCV::Make<bool>(sm)] |
			(Label >> lit(' ') >> lit("cdc") >> lit(' ') >> Char%',')[BindDCV::Make<char>(sm)]|
			(Label >> lit(' ') >> lit("cdc") >> lit(' ') >> String)[BindDCV::Make<char>(sm)];
		Label =as_string[(+(char_('A', 'Z')))];
		String= lit('"')>>(+((NullChar|EndLineChar|char_|wchar_)-'"'))>> lit('"');
		Comment = lit("/*") >>*((char_|wchar_)-"*/")>> lit("*/");
		LabelAdr = Label[_val = BindLabelAdr::Make(sm)];
		Register =
			lit("ax")[_val = sm.GetAX()] |
			lit("gr1")[_val = sm.GetGR(1)] |
			lit("gr2")[_val = sm.GetGR(2)] |
			lit("gr3")[_val = sm.GetGR(3)] |
			lit("gr4")[_val = sm.GetGR(4)] |
			lit("gr5")[_val = sm.GetGR(5)] |
			lit("gr6")[_val = sm.GetGR(6)] |
			lit("gr7")[_val = sm.GetGR(7)] |
			lit("gr8")[_val = sm.GetGR(8)];
		Adr = LabelAdr | Register|ValueAdr;
		Args1 = (Adr >> lit(' ') >> Adr)[_val = BindArgs1::Make()];
		Args3 = (Adr >> lit(' ') >> Adr >> lit(' ') >> Adr)[_val = BindArgs3::Make()];
		Args4 = (Adr >> lit(' ') >> Adr >> lit(' ') >> Adr >> lit(' ') >> Adr)[_val = BindArgs4::Make()];
		Args5 = (Adr)[_val=BindArgs5::Make()];
		Args = (Args1 | Args3 | Args4 | Args5);
		Order = (PRINT|ADD|LD|JMP|JMPB|CPAEQ|CPANEQ|INC|PUSH|POP|REF|DREF);
		JMP = lit("jmp") >> lit(' ') >> Args[_val = BindJMP::Make(sm)];
		JMPB = lit("jmpb") >> lit(' ') >> Args[_val = BindJMPB::Make(sm)];
		PRINT = 
			(lit("iprint") >> lit(' ') >> Args[_val = BindPRINT<int>::Make()])|
			(lit("dprint") >> lit(' ') >> Args[_val = BindPRINT<double>::Make()])|
			(lit("bprint") >> lit(' ') >> Args[_val = BindPRINT<bool>::Make()])|
			(lit("cprint") >> lit(' ') >> Args[_val = BindPRINT<char>::Make()])|
		    (lit("sprint") >> lit(' ') >> Args[_val = BindSPRINT::Make()]);
		LD=
			(lit("ild") >> lit(' ') >> Args[_val = BindLD<int>::Make()]) |
			(lit("dld") >> lit(' ') >> Args[_val = BindLD<double>::Make()]) |
			(lit("bld") >> lit(' ') >> Args[_val = BindLD<bool>::Make()]) |
			(lit("cld") >> lit(' ') >> Args[_val = BindLD<char>::Make()]);
		ADD =
			(lit("iadd") >> lit(' ') >> Args[_val = BindADD<int>::Make()]) |
			(lit("dadd") >> lit(' ') >> Args[_val = BindADD<double>::Make()]) |
			(lit("badd") >> lit(' ') >> Args[_val = BindADD<bool>::Make()]) |
			(lit("cadd") >> lit(' ') >> Args[_val = BindADD<char>::Make()]);
		PUSH =
			(lit("ipush") >> lit(' ') >> Args[_val = BindPUSH<int>::Make(sm)]) |
			(lit("dpush") >> lit(' ') >> Args[_val = BindPUSH<double>::Make(sm)]) |
			(lit("bpush") >> lit(' ') >> Args[_val = BindPUSH<bool>::Make(sm)]) |
			(lit("cpush") >> lit(' ') >> Args[_val = BindPUSH<char>::Make(sm)]);
		POP =
			(lit("ipop") >> lit(' ') >> Args[_val = BindPOP<int>::Make(sm)]) |
			(lit("dpop") >> lit(' ') >> Args[_val = BindPOP<double>::Make(sm)]) |
			(lit("bpop") >> lit(' ') >> Args[_val = BindPOP<bool>::Make(sm)]) |
			(lit("cpop") >> lit(' ') >> Args[_val = BindPOP<char>::Make(sm)]);
		INC =
			(lit("iinc") >> lit(' ') >> Args[_val = BindINC<int>::Make()]) |
			(lit("dinc") >> lit(' ') >> Args[_val = BindINC<double>::Make()]) |
			(lit("binc") >> lit(' ') >> Args[_val = BindINC<bool>::Make()]) |
			(lit("cinc") >> lit(' ') >> Args[_val = BindINC<char>::Make()]);
		CPAEQ =
			(lit("icpaeq") >> lit(' ') >> Args[_val = BindCPAEQ<int>::Make(sm)]) |
			(lit("dcpaeq") >> lit(' ') >> Args[_val = BindCPAEQ<double>::Make(sm)]) |
			(lit("bcpaeq") >> lit(' ') >> Args[_val = BindCPAEQ<bool>::Make(sm)]) |
			(lit("ccpaeq") >> lit(' ') >> Args[_val = BindCPAEQ<char>::Make(sm)]);
		CPANEQ =
			(lit("icpaneq") >> lit(' ') >> Args[_val = BindCPANEQ<int>::Make(sm)]) |
			(lit("dcpaneq") >> lit(' ') >> Args[_val = BindCPANEQ<double>::Make(sm)]) |
			(lit("bcpaneq") >> lit(' ') >> Args[_val = BindCPANEQ<bool>::Make(sm)]) |
			(lit("ccpaneq") >> lit(' ') >> Args[_val = BindCPANEQ<char>::Make(sm)]);
		REF =
			(lit("ref") >> lit(' ') >> Args[_val = BindREF::Make()]);
		DREF =
			(lit("idref") >> lit(' ') >> Args[_val = BindDREF<int>::Make()]) |
			(lit("ddref") >> lit(' ') >> Args[_val = BindDREF<double>::Make()]) |
			(lit("bdref") >> lit(' ') >> Args[_val = BindDREF<bool>::Make()]) |
			(lit("cdref") >> lit(' ') >> Args[_val = BindDREF<char>::Make()]) |
			(lit("pdref") >> lit(' ') >> Args[_val = BindDREF<void*>::Make()]);
	}
	//scriptコード全体をまとめる文法
	spt::qi::rule<Iterator>Code;
	//DC 命令
	spt::qi::rule<Iterator>DC;
	//PRINT命令
	spt::qi::rule<Iterator,OrderBase*>PRINT;
	//LD命令
	spt::qi::rule<Iterator, OrderBase*>LD;
	//ADD命令
	spt::qi::rule<Iterator, OrderBase*>ADD;
	//INC命令
	spt::qi::rule<Iterator, OrderBase*>INC;
	//PUSH命令
	spt::qi::rule<Iterator, OrderBase*>PUSH;
	//POP命令
	spt::qi::rule<Iterator, OrderBase*>POP;
	//CPAEQ命令
	spt::qi::rule<Iterator, OrderBase*>CPAEQ;
	//CPANEQ命令
	spt::qi::rule<Iterator, OrderBase*>CPANEQ;
	//JMP命令
	spt::qi::rule<Iterator, OrderBase*>JMP;
	//JMPB命令
	spt::qi::rule<Iterator, OrderBase*>JMPB;
	//REF命令
	spt::qi::rule<Iterator, OrderBase*>REF;
	//DREF命令
	spt::qi::rule<Iterator, OrderBase*>DREF;
	//実行命令
	spt::qi::rule<Iterator, OrderBase*>Order;
	//ラベル
	spt::qi::rule<Iterator,std::string()>Label;
	//ラベルが指すアドレス
	spt::qi::rule<Iterator, void*>LabelAdr;
	//レジスタのアドレス
	spt::qi::rule<Iterator, void*>Register;
	//アドレス
	spt::qi::rule<Iterator, void*>Adr;
	//Arg<1>
	spt::qi::rule<Iterator, Args<1>()>Args1;
	//Arg<3>
	spt::qi::rule<Iterator, Args<3>()>Args3;
	//Arg<4>
	spt::qi::rule<Iterator, Args<4>()>Args4;
	//Arg<5>
	spt::qi::rule<Iterator, Args<5>()>Args5;
	//Args<...>
	spt::qi::rule<Iterator, VarArgs()>Args;
	//char形式
	spt::qi::rule<Iterator,char()>Char;
	//null文字
	spt::qi::rule<Iterator, char()>NullChar;
	//改行文字
	spt::qi::rule<Iterator, char()>EndLineChar;
	//文字列
	spt::qi::rule<Iterator, std::vector<char>>String;
	//コメント
	spt::qi::rule<Iterator>Comment;
	//即値
	spt::qi::rule<Iterator, VarValue>Value;
	//即値アドレス
	spt::qi::rule<Iterator, void*>ValueAdr;

};


//構文解析実行
void Compile(std::string str) {
	Script<std::_String_iterator<std::_String_val<std::_Simple_types<char>>> > script_parser;
	auto first = str.begin();
	auto last = str.end();
	bool r = spt::qi::parse(first, last, script_parser);
	if (first != last) // 読み込みしきれてないとき
		throw "文法エラー";
	if (r == false)throw "文法エラー";
	script_parser.Run();
}

