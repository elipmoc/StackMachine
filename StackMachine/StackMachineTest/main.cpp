#include "StackMachine.h"
void main() {
	///スタックマシン用意
	StackMachine sm;
	///定数確保///
	sm.DC(0, "A");
	sm.DC(10, "MAX");
	sm.DC<std::string>("end", "ENDSTR");
	sm.DS(4, "TEST");
	sm.DS(4, "END");
	///命令作成///
	OrderVector orderv;
	orderv
		<<"TEST"<< MakeINC<int>()(Args<5>(sm["A"]))
		<<MakeCPA<int>()(Args<1>(sm["A"], sm["MAX"]), sm)
		<<MakePRINT<int>()(Args<5>(sm["A"]))
		<<MakeJMPB()(Args<1>(sm["END"],sm.GetAX()),sm)
		<<MakeJMP()(Args<5>(sm["TEST"]), sm)
		<<"END"<< MakePRINT<std::string>()(Args<5>(sm["ENDSTR"]));
	///命令格納///
	sm.SetOrderVector(orderv);
	///実行///
	sm.Run();
}