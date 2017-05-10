#include "StackMachineBuilder.h"
#include <fstream>
void main() {
	std::string path;
	std::string codeStr;
	std::string buf;
	path = "test.txt";
	//std::cin >> path;
	std::ifstream ifs(path);
	while (ifs&&std::getline(ifs, buf)) {
		codeStr += buf;
	}
	Compile(
		codeStr
	);
	std::cin >> path;
	/*///スタックマシン用意
	StackMachine sm;
	///定数確保///
	sm.DC(3.998, "A");
	sm.DS(sizeof(int), "B");
	///命令作成///
	OrderVector orderv;
	orderv
		<< MakeCAST(_i,_d,Args<1>(sm["B"], sm["A"]))
		<< MakePRINT(_i,Args<5>(sm["B"]));
	///命令格納///
	sm.SetOrderVector(orderv);
	///実行///
	sm.Run();*/
	/*
	double A=3.998;
	int B;
	B=(int)A;
	std::cout<<B<<std::endl;
	*/
}