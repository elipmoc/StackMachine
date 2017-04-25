#include "StackMachine.h"
#include <iostream>
void main() {
	int r[] = { 4 ,8};
	Adr adr1(r);
	int l = 3;
	Adr adr2(l);
	int x = 4;
	X x1(x);
	OrderBase* ld =MakeLD<int>::Make( MakeAdressArgs(adr1, x1, adr2));
	ld->Do();
	std::cout << *(int*)(adr1.value+4)<<std::endl<<*(int*)adr2.value;
}