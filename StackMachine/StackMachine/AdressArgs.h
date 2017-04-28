#pragma once
#include "AddressType.h"

//命令に渡すアドレス構造体定義
template<int N=0>
struct  AdressArgs{};

template<>
struct  AdressArgs<1>
{
	char* adr1;
	char* adr2;
	AdressArgs(void* adr1, void* adr2) {
		this->adr1 = (char*)adr1;
		this->adr2 = (char*)adr2;
	}
};
template<>
struct  AdressArgs<2>
{
	char* adr1;
	int* x1;
	char* adr2;
	AdressArgs(void* adr1,void* x1, void* adr2) {
		this->adr1 = (char*)adr1;
		this->adr2 = (char*)adr2;
		this->x1 = (int*)x1;
	}
};
template<>
struct  AdressArgs<3>
{
	char* adr1;
	char* adr2;
	int* x2;
	AdressArgs(void* adr1, void* adr2,void* x2) {
		this->adr1 = (char*)adr1;
		this->adr2 = (char*)adr2;
		this->x2 = (int*)x2;
	}
};
template<>
struct  AdressArgs<4>
{
	char* adr1;
	int* x1;
	char* adr2;
	int* x2;
	AdressArgs(void* adr1, void* x1, void* adr2,void* x2) {
		this->adr1 = (char*)adr1;
		this->adr2 = (char*)adr2;
		this->x1 = (int*)x1;
		this->x2 = (int*)x2;
	}
};
template<>
struct  AdressArgs<5>
{
	char* adr1;
	AdressArgs(void* adr1) {
		this->adr1 = (char*)adr1;
	}
};
template<>
struct  AdressArgs<6>
{
	char* adr1;
	int* x1;
	AdressArgs(void* adr1, void* x1) {
		this->adr1 = (char*)adr1;
		this->x1 = (int*)x1;
	}
};


//別名定義
template<int N>
using Args = AdressArgs<N>;
/*
//Args作成
auto MakeArgs(Adr& adr1, Adr& adr2) {
	Args<1> ad = { adr1.value,adr2.value };
	return ad;
};

auto MakeArgs(Adr& adr1,X& x1, Adr& adr2) {
	Args<2> ad = { adr1.value,x1.value,adr2.value };
	return ad;
};

auto MakeArgs(Adr& adr1, Adr& adr2, X& x2) {
	Args<3> ad = { adr1.value,adr2.value,x2.value };
	return ad;
};

auto MakeArgs(Adr& adr1,X& x1, Adr& adr2, X& x2) {
	Args<4> ad = { adr1.value,x1.value,adr2.value,x2.value };
	return ad;
};*/