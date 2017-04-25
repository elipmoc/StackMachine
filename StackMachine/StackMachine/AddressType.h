#pragma once

template<typename Type>
struct Pointer
{	
	template<typename T>
	Pointer(T& p) : value((Type)&p) {}
	template<typename T>
	Pointer(T* p):value((Type)p) {}
    Type value;
};

struct Adr:Pointer<char*>
{
	template<typename T>
	Adr(T& t) :Pointer(t) {}
};

struct X :Pointer<int*>
{
	template<typename T>
	X(T& t) :Pointer(t) {}
};