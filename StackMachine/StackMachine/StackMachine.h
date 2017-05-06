#pragma once
#include "AdressArgs.h"
#include "type.h"
#include "Order.h"
#include <iostream>
#include "Print.h"
#include <map>
#include <string>
#include <vector>
#include "OrderVector.h"
#include <type_traits>

//スタックマシン
class StackMachine {
	//ラベル記憶
	std::map<std::string, void*> label;
	//即値ラベル記憶
	std::map<int, void*> ilabel;
	std::map<double, void*> dlabel;
	std::map<bool, void*> blabel;
	std::map<char, void*> clabel;
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
	void* GetAX() {
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
	//即値命令
	void* ValueLabel(int t) {
		if (ilabel.count(t) == 1)return ilabel[t];
		int* tp = new (&Memory[usedIndex]) int;
		*tp = t;
		ilabel[t] = &Memory[usedIndex];
		usedIndex += sizeof(int);
		return ilabel[t];
	};
	void* ValueLabel(double t) {
		if (dlabel.count(t) == 1)return dlabel[t];
		double* tp = new (&Memory[usedIndex]) double;
		*tp = t;
		dlabel[t] = &Memory[usedIndex];
		usedIndex += sizeof(double);
		return dlabel[t];
	};
	void* ValueLabel(bool t) {
		if (blabel.count(t) == 1)return blabel[t];
		bool* tp = new (&Memory[usedIndex]) bool;
		*tp = t;
		blabel[t] = &Memory[usedIndex];
		usedIndex += sizeof(double);
		return blabel[t];
	};
	void* ValueLabel(char t) {
		if (clabel.count(t) == 1)return clabel[t];
		char* tp = new (&Memory[usedIndex]) char;
		*tp = t;
		clabel[t] = &Memory[usedIndex];
		usedIndex += sizeof(char);
		return clabel[t];
	};

	//DC命令。(即値,ラベル名)
	template<typename T>
	void DC(T t, std::string labelName) {
		if (label.count(labelName) == 1)throw "ラベルが再定義されました";
		T* tp=new (&Memory[usedIndex]) T;
		*tp= t;
		label[labelName] = &Memory[usedIndex];
		usedIndex += sizeof(T);
	};


	//配列DCV命令。(vector{即値,即値,即値,即値....},ラベル名)
	template<typename T>
	void DCV(std::vector<T> t, std::string labelName) {
		if (label.count(labelName) == 1)throw "ラベルが再定義されました";
		label[labelName] = &Memory[usedIndex];
		for (auto it = t.begin(); it != t.end(); it++) {
			T* tp = new (&Memory[usedIndex]) T;
			*tp = *it;
			usedIndex += sizeof(T);
		}
	};
	//DS命令。(即値,ラベル名)
	void DS(int size, std::string labelName) {
		if (label.count(labelName) == 1)throw "ラベルが再定義されました";
		label[labelName] = &Memory[usedIndex];
		usedIndex += size;
	};
	void* operator[](std::string labelName) {
		if (label.count(labelName) == 0) {
			DS(4, labelName);
		}
		return label[labelName];
	}

};

#include "LD.h"
#include "JMP.h"
#include "ADD.h"
#include "CPA.h"
#include "JMPB.h"
#include "INC.h"
#include "Ref.h"
#include "DRef.h"
#include "LDR.h"
#include "CAST.h"