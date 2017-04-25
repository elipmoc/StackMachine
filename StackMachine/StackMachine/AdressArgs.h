#pragma once
#include "AddressType.h"

template<int N=0>
struct  AdressArgs{};

template<>
struct  AdressArgs<1>
{
	char* adr1;
	char* adr2;
};
template<>
struct  AdressArgs<2>
{
	char* adr1;
	int* x1;
	char* adr2;
};
template<>
struct  AdressArgs<3>
{
	char* adr1;
	char* adr2;
	int* x2;
};
template<>
struct  AdressArgs<4>
{
	char* adr1;
	int* x1;
	char* adr2;
	int* x2;
};

auto MakeAdressArgs(Adr& adr1, Adr& adr2) {
	AdressArgs<1> ad = { adr1.value,adr2.value };
	return ad;
};

auto MakeAdressArgs(Adr& adr1,X& x1, Adr& adr2) {
	AdressArgs<2> ad = { adr1.value,x1.value,adr2.value };
	return ad;
};

auto MakeAdressArgs(Adr& adr1, Adr& adr2, X& x2) {
	AdressArgs<3> ad = { adr1.value,adr2.value,x2.value };
	return ad;
};

auto MakeAdressArgs(Adr& adr1,X& x1, Adr& adr2, X& x2) {
	AdressArgs<4> ad = { adr1.value,x1.value,adr2.value,x2.value };
	return ad;
};