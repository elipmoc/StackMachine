#include "..\StackMachine\StackMachine.h"
#include "CustomVariant.h"
#include "BindOrder.h"
#include "StackMachineBuilder.h"
#include "TemplateInstantiation.h"


using Iterator = std::string::iterator;

struct Script::ImplScript :spt::qi::grammar<Iterator> {
private:
	StackMachine sm;
	OrderVector ov;
	auto AddOrder() {
		return phx::bind([this](OrderBase* ob) {ov << ob; }, spt::_1);
	}
	auto AddOrderLabel() {
		return phx::bind([this](std::string str) { ov << str; }, spt::_1);
	}
	void InitRules();
public:
	RunMachine CreateRunMachine() { sm.SetOrderVector(ov); return RunMachine(sm); }
	ImplScript() :ImplScript::base_type(Code) {
		InitRules();
	}
	//scriptコード全体をまとめる文法
	spt::qi::rule<Iterator>Code;
	//1個以上のスペース
	spt::qi::rule<Iterator>oneSpace;
	//0個以上のスペース
	spt::qi::rule<Iterator>zeroSpace;
	//引数のカンマ
	spt::qi::rule<Iterator>kanma;
	//DC 命令
	spt::qi::rule<Iterator>DC;
	//END命令
	spt::qi::rule<Iterator, OrderBase*>END;
	//PRINT命令
	spt::qi::rule<Iterator, OrderBase*>PRINT;
	//SCAN命令
	spt::qi::rule<Iterator, OrderBase*>SCAN;
	//LD命令
	spt::qi::rule<Iterator, OrderBase*>LD;
	//LDA命令
	spt::qi::rule<Iterator, OrderBase*>LDR;
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
	//CAST命令
	spt::qi::rule<Iterator, OrderBase*>CAST;
	//CALL命令
	spt::qi::rule<Iterator, OrderBase*>CALL;
	//実行命令
	spt::qi::rule<Iterator, OrderBase*>Order;
	//ラベル
	spt::qi::rule<Iterator, std::string()>Label;
	//ラベルが指すアドレス
	spt::qi::rule<Iterator, void*>LabelAdr;
	//レジスタのアドレス
	spt::qi::rule<Iterator, void*>Register;
	//アドレス
	spt::qi::rule<Iterator, void*>Adr;
	//Args<1>
	spt::qi::rule<Iterator, Args<1>()>Args1;
	//Args<2>
	spt::qi::rule<Iterator, Args<2>()>Args2;
	//Args<3>
	spt::qi::rule<Iterator, Args<3>()>Args3;
	//Args<4>
	spt::qi::rule<Iterator, Args<4>()>Args4;
	//命令がとる引数
	spt::qi::rule<Iterator, VarArgs()>Args;
	//char形式
	spt::qi::rule<Iterator, char()>Char;
	//アドレス即値形式
	spt::qi::rule<Iterator, int()>AdressValue;
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

void Script::ImplScript::InitRules() {
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
		(zeroSpace >> DC >> zeroSpace >> lit(';'))
			|
			(zeroSpace >> -(Label[AddOrderLabel()] >> oneSpace) >> Order[AddOrder()] >> zeroSpace >> lit(';'))
			|
			(zeroSpace >> Comment)
			);
	oneSpace = +lit(' ');
	zeroSpace = *lit(' ');
	kanma = zeroSpace >> lit(',') >> zeroSpace;
	NullChar = lit("\\0")[_val = '\0'];
	EndLineChar = lit("\\n")[_val = '\n'];
	Char = lit('\'') >> (NullChar | EndLineChar | char_) - '\'' >> lit('\'');
	AdressValue = lit('p') >> int_;
	Value = strict_double | int_ | Char | bool_;
	ValueAdr =
		Value[_val = BindValueAdr::Make(sm)] |
		String[_val = BindStringAdr::Make(sm)] |
		AdressValue[_val=phx::bind([](int& hoge) {return (void*)hoge;},_1)];
	DC =
		(lit("idc") >> oneSpace >> Label >> zeroSpace >> lit('=') >> zeroSpace >> int_%',')[BindDCV::Make<int>(sm)] |
		(lit("ddc") >> oneSpace >> Label >> zeroSpace >> lit('=') >> zeroSpace >> double_%',')[BindDCV::Make<double>(sm)] |
		(lit("bdc") >> oneSpace >> Label >> zeroSpace >> lit('=') >> zeroSpace >> bool_%',')[BindDCV::Make<bool>(sm)] |
		(lit("cdc") >> oneSpace >> Label >> zeroSpace >> lit('=') >> zeroSpace >> Char%',')[BindDCV::Make<char>(sm)] |
		(lit("cdc") >> oneSpace >> Label >> zeroSpace >> lit('=') >> zeroSpace >> String)[BindDCV::Make<char>(sm)];
	Label = as_string[(+(char_('A', 'Z')))];
	String = lit('"') >> (+((NullChar | EndLineChar | char_ | wchar_) - '"')) >> lit('"');
	Comment =
		(lit("/*") >> *((char_ | wchar_) - "*/") >> lit("*/")) |
		(lit("//") >> *((char_ | wchar_)));
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
		lit("gr8")[_val = sm.GetGR(8)] |
		lit("pr")[_val = sm.GetPR()] |
		lit("sp")[_val = sm.GetSP()] |
		lit("bp")[_val = sm.GetBP()];

	Adr = LabelAdr | Register | ValueAdr;
	Args1 = (Adr)[_val = BindArgs1::Make()];
	Args2 = (Adr >> kanma >> Adr)[_val = BindArgs2::Make()];
	Args3 = (Adr >> kanma >> Adr >> kanma >> Adr)[_val = BindArgs3::Make()];
	Args4 = (Adr >> kanma >> Adr >> kanma >> Adr >> kanma >> Adr)[_val = BindArgs4::Make()];
	Args = zeroSpace >> lit('(') >> zeroSpace >> (Args4 | Args3 | Args2 | Args1) >> zeroSpace >> lit(')');
	Order = (END | PRINT | SCAN | ADD | LD | LDR | JMP | JMPB | CPAEQ | CPANEQ | INC | PUSH | POP | REF | DREF | CAST|CALL);
	JMP = lit("jmp") >> Args[_val = BindJMP::Make(sm)];
	JMPB = lit("jmpb") >> Args[_val = BindJMPB::Make(sm)];
	PRINT =
		(lit("iprint") >> Args[_val = BindPRINT<int>::Make()]) |
		(lit("dprint") >> Args[_val = BindPRINT<double>::Make()]) |
		(lit("bprint") >> Args[_val = BindPRINT<bool>::Make()]) |
		(lit("cprint") >> Args[_val = BindPRINT<char>::Make()]) |
		(lit("sprint") >> Args[_val = BindSPRINT::Make()]);
	SCAN =
		(lit("iscan") >> Args[_val = BindSCAN<int>::Make()]) |
		(lit("dscan") >> Args[_val = BindSCAN<double>::Make()]) |
		(lit("bscan") >> Args[_val = BindSCAN<bool>::Make()]) |
		(lit("cscan") >> Args[_val = BindSCAN<char>::Make()]);
	LD =
		(lit("ild") >> Args[_val = BindLD<int>::Make()]) |
		(lit("dld") >> Args[_val = BindLD<double>::Make()]) |
		(lit("bld") >> Args[_val = BindLD<bool>::Make()]) |
		(lit("cld") >> Args[_val = BindLD<char>::Make()]);
	LDR =
		(lit("ildr") >> Args[_val = BindLDR<int>::Make()]) |
		(lit("dldr") >> Args[_val = BindLDR<double>::Make()]) |
		(lit("bldr") >> Args[_val = BindLDR<bool>::Make()]) |
		(lit("cldr") >> Args[_val = BindLDR<char>::Make()]);
	ADD =
		(lit("iadd") >> Args[_val = BindADD<int>::Make()]) |
		(lit("dadd") >> Args[_val = BindADD<double>::Make()]) |
		(lit("cadd") >> Args[_val = BindADD<char>::Make()]) |
		(lit("padd") >> Args[_val = BindADD<char*>::Make()]);
	PUSH =
		(lit("ipush") >> Args[_val = BindPUSH<int>::Make(sm)]) |
		(lit("dpush") >> Args[_val = BindPUSH<double>::Make(sm)]) |
		(lit("bpush") >> Args[_val = BindPUSH<bool>::Make(sm)]) |
		(lit("cpush") >> Args[_val = BindPUSH<char>::Make(sm)]) |
		(lit("ppush") >> Args[_val = BindPUSH<void*>::Make(sm)]);
	POP =
		(lit("ipop") >> Args[_val = BindPOP<int>::Make(sm)]) |
		(lit("dpop") >> Args[_val = BindPOP<double>::Make(sm)]) |
		(lit("bpop") >> Args[_val = BindPOP<bool>::Make(sm)]) |
		(lit("cpop") >> Args[_val = BindPOP<char>::Make(sm)]) |
		(lit("ppop") >> Args[_val = BindPOP<void*>::Make(sm)]);
	INC =
		(lit("iinc") >> Args[_val = BindINC<int>::Make()]) |
		(lit("dinc") >> Args[_val = BindINC<double>::Make()]) |
		(lit("cinc") >> Args[_val = BindINC<char>::Make()]);
	CPAEQ =
		(lit("icpaeq") >> Args[_val = BindCPAEQ<int>::Make(sm)]) |
		(lit("dcpaeq") >> Args[_val = BindCPAEQ<double>::Make(sm)]) |
		(lit("bcpaeq") >> Args[_val = BindCPAEQ<bool>::Make(sm)]) |
		(lit("ccpaeq") >> Args[_val = BindCPAEQ<char>::Make(sm)]);
	CPANEQ =
		(lit("icpaneq") >> Args[_val = BindCPANEQ<int>::Make(sm)]) |
		(lit("dcpaneq") >> Args[_val = BindCPANEQ<double>::Make(sm)]) |
		(lit("bcpaneq") >> Args[_val = BindCPANEQ<bool>::Make(sm)]) |
		(lit("ccpaneq") >> Args[_val = BindCPANEQ<char>::Make(sm)]);
	REF =
		(lit("ref") >> Args[_val = BindREF::Make()]);
	DREF =
		(lit("idref") >> Args[_val = BindDREF<int>::Make()]) |
		(lit("ddref") >> Args[_val = BindDREF<double>::Make()]) |
		(lit("bdref") >> Args[_val = BindDREF<bool>::Make()]) |
		(lit("cdref") >> Args[_val = BindDREF<char>::Make()]) |
		(lit("pdref") >> Args[_val = BindDREF<void*>::Make()]);
	CAST =
		(lit("icastd") >> Args[_val = BindCAST<int, double>::Make()]) |
		(lit("dcasti") >> Args[_val = BindCAST<double, int>::Make()]) |
		(lit("icastc") >> Args[_val = BindCAST<int, char>::Make()]) |
		(lit("ccasti") >> Args[_val = BindCAST<char, int>::Make()]) |
		(lit("icastb") >> Args[_val = BindCAST<int, bool>::Make()]) |
		(lit("bcasti") >> Args[_val = BindCAST<bool, int>::Make()]) |
		(lit("dcastc") >> Args[_val = BindCAST<double, char>::Make()]) |
		(lit("ccastd") >> Args[_val = BindCAST<char, double>::Make()]) |
		(lit("dcastb") >> Args[_val = BindCAST<double, bool>::Make()]) |
		(lit("bcastd") >> Args[_val = BindCAST<bool, double>::Make()]) |
		(lit("ccastb") >> Args[_val = BindCAST<char, bool>::Make()]) |
		(lit("bcastc") >> Args[_val = BindCAST<bool, char>::Make()]);
	END = lit("end")[_val = BindEND::Make(sm)];
	CALL = lit("call")>>Args[_val = BindCALL::Make(sm)];
}

RunMachine Script::CreateRunMachine() {
	return implScript->CreateRunMachine();
}

bool Script::Parse(std::string::iterator& first, std::string::iterator& last) {
	return spt::qi::parse(first, last, *implScript);
}

Script::Script() {
	implScript = new ImplScript;
}
