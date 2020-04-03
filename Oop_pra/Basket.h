#ifndef BASKET_H
#define BASKET_H
#include<map>
#include<set>
#include<memory>
#include<iostream>
#include"Bulk_quote.h"
#include"disc_quote.h"
#include"Quote.h"
using namespace std;
//智能指针在memory里面
class Basket
{
public:
	Basket();
	~Basket();
	//double add_item(const std::shared_ptr<Quote>& sale) {
	//	items.insert(sale);
	//}
	//解释为什么在参数这里可以使用基类Quote类而不需要担心转换时丢弃掉部分派生类内容。
	void add_item(const Quote& sale) {
		items.insert(std::shared_ptr<Quote>(sale.clone()));
	}
	void add_item(Quote&& sale) {
		items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
	}
	double total_receipt(ostream &os)const {
		double sum = 0.0;
		//Returns an iterator pointing to the first element
		// in the container which is considered to go after val.
		//所以
		for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
			sum += print_total(os, **iter, items.count(*iter));
		}
		os << "Total Sale: " << sum << endl;
		return sum;
	}
private:
	//std::multimap < std::shared_ptr<Quote>, decltype()
	static bool compare(const std::shared_ptr<Quote>& lhs, const std::shared_ptr<Quote> &rhs)
	{	return lhs->isbn() < rhs->isbn();	}
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};

};

#endif // !BASKET_H
