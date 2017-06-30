#pragma once

struct Order {
	OrderBase* ob;
	std::string label;
	Order(OrderBase* ob, std::string label) {
		this->ob = ob;
		this->label = label;
	}
};

//別名定義
using OrderVector = std::vector<Order>;
static std::string __label="";
//グローバル演算子オーバーロード
inline OrderVector& operator<<(OrderVector& ov, OrderBase* ob) {
	
	ov.push_back(Order(ob,__label));
	__label = "";
	return ov;
}
inline OrderVector& operator<<(OrderVector& ov, std::string _label) {
	if (__label != "")throw std::string("labelを入れたあとはOrderBase*を入れて下さい");
	__label = _label;
	return ov;
}