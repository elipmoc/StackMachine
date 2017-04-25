#pragma once
#include "AddressType.h"

template<int N=0>
struct  AdressData{};

template<>
struct  AdressData<1>
{
	char* adr1;
	char* adr2;
};
template<>
struct  AdressData<2>
{
	char* adr1;
	int* x1;
	char* adr2;
};
template<>
struct  AdressData<3>
{
	char* adr1;
	char* adr2;
	int* x2;
};
template<>
struct  AdressData<4>
{
	char* adr1;
	int* x1;
	char* adr2;
	int* x2;
};

auto MakeAdressData(Adr& adr1, Adr& adr2) {
	AdressData<1> ad = { adr1.value,adr2.value };
	return ad;
};

auto MakeAdressData(Adr& adr1,X& x1, Adr& adr2) {
	AdressData<2> ad = { adr1.value,x1.value,adr2.value };
	return ad;
};

auto MakeAdressData(Adr& adr1, Adr& adr2, X& x2) {
	AdressData<3> ad = { adr1.value,adr2.value,x2.value };
	return ad;
};

auto MakeAdressData(Adr& adr1,X& x1, Adr& adr2, X& x2) {
	AdressData<4> ad = { adr1.value,x1.value,adr2.value,x2.value };
	return ad;
};