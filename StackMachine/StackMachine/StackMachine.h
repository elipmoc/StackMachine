#pragma once
#include "AddressType.h"
#include "AdressArgs.h"
#include "Order.h"
#include "LD.h"
#include <map>
#include <string>

//スタックマシン
class StackMachine {
	//ラベル記憶
	std::map<std::string, void*> label;
	//メモリ領域
	char* Memory = new char[65536];
	//最後尾の命令のポインタが格納されているインデックス
	int endOrder;
public:
	//spレジスタのアドレス
	char* GetSP() {
		return &Memory[0];
	};
	//bpレジスタのアドレス
	char* GetBP() {
		return &Memory[4];
	};
	//prレジスタのアドレス
	char* GetPR() {
		return &Memory[8];
	}
	//axレジスタのアドレス
	char* GetAX() {
		return &Memory[12];
	}
	//GR(i)レジスタのアドレス
	char* const GetGR(int i) {
		if (!(i >= 1 && i <= 8))throw "GetGR():範囲外です";
		return &Memory[20+(i-1)*8];
	};

StackMachine()
{
	//はじめの命令のポインタが格納されてるポインタを保存
	*(void**)GetPR() =&Memory[84] ;
	endOrder = 80;
}
void AddOrder(OrderBase* order) {
	endOrder += 4;
	*(void**)(&Memory[endOrder]) = order;
}
};