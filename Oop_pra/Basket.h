#ifndef BASKET_H
#define BASKET_H
#include<map>
#include<set>
#include<memory>
#include<iostream>
#include"Bulk_quote.h"
#include"disc_quote.h"
#include"Quote.h"
//智能指针在memory里面
class Basket
{
public:
	Basket();
	~Basket();
	double add_item(const std::shared_ptr<Quote>& sale) {
		items.insert(sale);
	}
	double total_receipt()const {
		double ret = 0.0;
		for (auto a : items) {
			ret += a->net_price;
		}
		std::cout << "The total in Basket are: " << ret << endl;
		return ret;
	}
private:
	//std::multimap < std::shared_ptr<Quote>, decltype()
	static bool compare(const std::shared_ptr<Quote>& lhs, const std::shared_ptr<Quote> &rhs)
	{	return lhs->isbn() < rhs->isbn();	}
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};

};


#endif // !BASKET_H
