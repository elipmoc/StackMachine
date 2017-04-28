#include "StackMachine.h"
void main() {
	///仮想マシン用意
	StackMachine sm;
	///定数確保///
	//A DC 0
	sm.DC(0, "A");
	sm.DC(1, "B");
	sm.DS(4, "TEST");
	///命令作成///
	OrderVector orderv;
	orderv

		//TEST ADD A,B
		<< "TEST"<< MakeADD<int>()(Args<1>(sm["A"],sm["B"]))

		//PRINT A
		<< MakePRINT<int>()(Args<5>(sm["A"]))

		//JMP TEST
		<< MakeJMP()(Args<5>(sm["TEST"]),sm);

	///命令格納///
	sm.SetOrderVector(orderv);
	///実行///
	sm.Run();
}