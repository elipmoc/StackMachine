#pragma once
#include <array>
#include <tuple>
#include <utility>
//命令に渡すアドレス構造体定義<引数の数>
template<int N>
struct  AdressArgs {
	std::array<void*, N> adrs;
public:
	AdressArgs(std::array<void*,N> _adrs):adrs(_adrs)
	{
	}
	AdressArgs() {}
	template<int M>
	char* GetAdr() {
		static_assert(M<= N&&M>0, "array range out");
		return (char*)adrs[M-1];
	}
};

/*template<>
struct  AdressArgs<1>
{
	char* adr1;
	AdressArgs(void* adr1) {
		this->adr1 = (char*)adr1;
	}
	AdressArgs() {}

};

template<>
struct  AdressArgs<2>
{
	char* adr1;
	char* adr2;
	AdressArgs(void* adr1, void* adr2) {
		this->adr1 = (char*)adr1;
		this->adr2 = (char*)adr2;
	}
	AdressArgs(){}
};

template<>
struct  AdressArgs<3>
{
	char* adr1;
	char* adr2;
	char* adr3;
	AdressArgs(void* adr1,void* adr2, void* adr3) {
		this->adr1 = (char*)adr1;
		this->adr2 = (char*)adr2;
		this->adr3 = (char*)adr3;
	}
	AdressArgs(){}
};

template<>
struct  AdressArgs<4>
{
	char* adr1;
	char* adr2;
	char* adr3;
	char* adr4;
	AdressArgs(void* adr1, void* adr2, void* adr3,void* adr4) {
		this->adr1 = (char*)adr1;
		this->adr2 = (char*)adr2;
		this->adr3 = (char*)adr3;
		this->adr4 = (char*)adr4;
	}
	AdressArgs() {}
};*/

//エイリアス定義
template<int N>
using Args = AdressArgs<N>;

//AdressArgs生成関数
template<class ...Args_>
auto Make_Arags(Args_&&... args) {
	return AdressArgs<sizeof...(Args_)>({ std::forward<Args_>(args)... });
}
template<class ...Args_>
auto Make_Arags_for_tuple(const std::tuple<Args_...>& tuple) {
	return Make_Arags_for_tuple_impl (tuple, std::make_index_sequence<sizeof...(Args_)>());
}
template<size_t ...index,class ...Args_>
auto Make_Arags_for_tuple_impl(const std::tuple<Args_...>& tuple,std::index_sequence<index...>) {
	return AdressArgs<sizeof...(index)>({ (std::get<index>(tuple))... });
}