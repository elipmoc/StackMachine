#include "StackMachine.h"
void main() {
	///スタックマシン用意
	StackMachine sm;
	///定数確保///
	sm.DC(3.998, "A");
	sm.DS(sizeof(double), "B");
	///命令作成///
	OrderVector orderv;
	orderv
		<< MakeCAST<int, double>()(Args<1>(sm["B"], sm["A"]))
		<< MakePRINT<int>()(Args<5>(sm["B"]));
	///命令格納///
	sm.SetOrderVector(orderv);
	///実行///
	sm.Run();
}