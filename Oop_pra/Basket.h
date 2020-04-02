#ifndef BASKET_H
#define BASKET_H
#include<map>
#include<set>
#include<memory>
#include"Quote.h"
#include"SelfQuote.h"
//智能指针在memory里面
class Basket
{
public:
	Basket();
	~Basket();
	double add_item(const std::shared_ptr<Quote>& sale) {
		items.insert(sale);
	}
private:
	//std::multimap < std::shared_ptr<Quote>, decltype()
	static bool compare(const std::shared_ptr<Quote>& lhs, const std::shared_ptr<Quote> &rhs)
	{	return lhs->isbn() < rhs->isbn();	}
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};

};


#endif // !BASKET_H
