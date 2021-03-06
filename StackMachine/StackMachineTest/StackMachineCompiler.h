#pragma once
#include "StackMachineBuilder.h"
#include "StackMachine.h"

class StackMachineCompiler {
	VirtualMachineBuilder::Script script_parser;
public:
	void Run() {
		script_parser.CreateRunMachine().Run();
	}
	//構文解析実行
	void Compile(std::string str) {
		auto first = str.begin();
		auto last = str.end();
		bool r = script_parser.Parse(first, last);
		if (first != last) // 読み込みしきれてないとき
			throw std::string("Syntax Error  ");
		if (r == false)throw std::string("Syntax Error  ");
	}
};