#pragma once
struct BindEND
{
	static OrderBase* _Make(StackMachine* sm) {
		return MakeEND(*sm);
	}
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindEND::_Make, &sm);
	}
};