#ifndef SELFQUOTE_H
#define SELFQUOTE_H
#include<iostream>
#include<string>
#include"Quote.h"
//基类Quote在Quote.h中
class Disc_quote:public Quote
{
public:
	Disc_quote(const std::string book, double price, size_t q, double dis) :Quote(book, price),quantity(q) {};

	Disc_quote(const Disc_quote& dq) :
		Quote(dq), quantity(dq.quantity), discount(dq.discount){}

	// move constructor
	Disc_quote(Disc_quote&& dq) noexcept :
		Quote(std::move(dq)), quantity(std::move(dq.quantity)), discount(std::move(dq.discount)){}

	Disc_quote& operator =(const Disc_quote& rhs)
	{
		Quote::operator =(rhs);
		this->quantity = rhs.quantity;
		this->discount = rhs.discount;
		return *this;
	}

	// move =()
	Disc_quote& operator =(Disc_quote&& rhs) noexcept
	{
		if (*this != rhs)
		{
			Quote::operator =(std::move(rhs));
			this->quantity = std::move(rhs.quantity);
			this->discount = std::move(rhs.discount);
		}
		return *this;
	}
	//后面加上=0表示为抽象基类，不允许创建抽象基类的对象
	double net_price(std::size_t n) const = 0;
//protected而非private
protected:
	std::size_t quantity;
	double discount;
};
class Bulk_quote :public Disc_quote
{
public:
	Bulk_quote(const std::string& book, double sales_price, std::size_t qty, double _discount):Disc_quote(book,sales_price,qty,_discount) {};
	Bulk_quote(const Bulk_quote& rhs) :Disc_quote(rhs) {}
	Bulk_quote(Bulk_quote&& rhs) :Disc_quote(move(rhs)) {};

	double net_price(std::size_t n)const override {
		if (n >= quantity) {
			return n * (1 - discount) * price;
		}
		else
			return n * price;
	}

};

//limited_quote成员数量和Bulk_quote的是一样的，就不写这一个的拷贝控制成员了
class Limited_Quote :public Disc_quote
{
public:
	Limited_Quote(const std::string& book, double sales_price, std::size_t qty, double _discount) :Disc_quote(book, sales_price,qty,_discount) {};
	
	
	double net_price(size_t n)const override {
		if (n < quantity) {
			return n * (1 - discount) * price;
		}
		else
		{
			return n * price - discount * price *quantity;
		}
	}

};

#endif // !SELFQUOTE_H
