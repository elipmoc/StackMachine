#pragma once
#include "AdressArgs.h"
#include "Order.h"
#include <iostream>
#include "Print.h"
#include <map>
#include <string>
#include <vector>
#include "OrderVector.h"

//スタックマシン
class StackMachine {
	//ラベル記憶
	std::map<std::string, void*> label;
	//メモリ領域
	char* Memory = new char[65536];
	//Memoryの空き領域の先頭アドレスを指すインデックス
	int usedIndex;
	//最後の命令が格納されているアドレス
	char* endOrderAdr;
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
	char** GetPR() {
		return (char**)&Memory[8];
	}
	//axレジスタのアドレス
	char* GetAX() {
		return &Memory[12];
	}
	//GR(i)レジスタのアドレス
	char* GetGR(int i) {
		if (!(i >= 1 && i <= 8))throw "GetGR():範囲外です";
		return &Memory[20 + (i - 1) * 8];
	};

	StackMachine()
	{
		usedIndex = 84;
	};
	//命令格納
	void SetOrderVector(OrderVector orders) {
		//はじめの命令のポインタが格納されてるポインタを保存
		*GetPR() = &Memory[usedIndex];
		for (int i = 0; i < orders.size(); i++) {
			AddOrder(orders[i]);
		}
		endOrderAdr = &Memory[usedIndex - 4];
	}
	//実行
	void Run() {
		while (true)
		{
			(*(OrderBase**)(*GetPR()))->Do();
			*GetPR() += 4;
			if (*GetPR() == endOrderAdr + 4)return;
		}
	}
private:
	void AddOrder(Order& order) {
		*(void**)(&Memory[usedIndex]) = order.ob;
		if (order.label != "") {
			*(char**)label[order.label] = &Memory[usedIndex];
		}
		usedIndex += 4;
	};
public:
	//DC命令。(即値,ラベル名)
	template<typename T>
	void DC(T t, std::string labelName) {
		if (label.count(labelName) == 1)throw "ラベルが再定義されました";
		*(T*)(&Memory[usedIndex]) = t;
		label[labelName] = &Memory[usedIndex];
		usedIndex += sizeof(T);
	};
	//DS命令。(即値,ラベル名)
	void DS(int size, std::string labelName) {
		if (label.count(labelName) == 1)throw "ラベルが再定義されました";
		label[labelName] = &Memory[usedIndex];
		usedIndex += size;
	};

	void* GetLabel(std::string labelName) {
		if (label.count(labelName) == 0)throw "未定義のラベルにアクセスしようとしました";
		return label[labelName];
	};

	void* operator[](std::string labelName) {
		if (label.count(labelName) == 0)throw "未定義のラベルにアクセスしようとしました";
		return label[labelName];
	}

};

#include "LD.h"
#include "JMP.h"
#include "ADD.h"