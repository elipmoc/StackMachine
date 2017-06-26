#pragma once
struct BindRET
{
	static OrderBase* _Make(StackMachine* sm) {
		return MakeRET(*sm);
	}
	static auto Make(StackMachine& sm) {
		return phx::bind(&BindRET::_Make, &sm);
	}
};